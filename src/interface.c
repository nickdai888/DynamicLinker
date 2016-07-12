#include "..\inc\interface.h"
#include "..\inc\plt_lyr.h"
#include "..\inc\loader.h"
#include "..\inc\linker.h"

DLL_INSTANCE_HANDLER LoadLibrary(WCHAR *lpLibrary_name)
{
	UINT rd_count = 0;
	UINT section_header_table_len = 0;
	DLL_INSTANCE_HANDLER dll_instance_hdr = (DLL_INSTANCE_HANDLER)GLOBAL_MALLOC(sizeof(struct DLL_INSTANCE));
	if(NULL == dll_instance_hdr)
	{
		return NULL;
	}
	else
	{
		dll_memset(dll_instance_hdr,0,sizeof(struct DLL_INSTANCE));
	}
	do
	{
		dll_wcscpy(dll_instance_hdr->dll_file_path,lpLibrary_name);
		dll_instance_hdr->file_handler = dll_fopen(dll_instance_hdr->dll_file_path, DLL_FS_READ_ONLY);
		#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
			if(dll_instance_hdr->file_handler < 0)
		  #else
			if(dll_instance_hdr->file_handler == NULL)
		#endif
			break;
		dll_fseek( dll_instance_hdr->file_handler, 0, DLL_FS_FILE_BEGIN );
		dll_fread(dll_instance_hdr->file_handler , &dll_instance_hdr->elf_headr, sizeof(Elf32_Ehdr), &rd_count);
		if(rd_count == 0)
			break;
		DLL_TRACE("IMAGE HAS %d SECTIONS,%d PROGRAM SEGMENTS\n",dll_instance_hdr->elf_headr.e_shnum,dll_instance_hdr->elf_headr.e_phnum);
		section_header_table_len = sizeof(Elf32_Shdr)*dll_instance_hdr->elf_headr.e_shnum;
		dll_instance_hdr->elf_section_header_table_ptr = (Elf32_Shdr*)GLOBAL_MALLOC(section_header_table_len );
		if(NULL == dll_instance_hdr->elf_section_header_table_ptr)
			break;
		dll_memset(dll_instance_hdr->elf_section_header_table_ptr, 0, section_header_table_len);
		dll_fseek(dll_instance_hdr->file_handler , dll_instance_hdr->elf_headr.e_shoff,  DLL_FS_FILE_BEGIN);
		dll_fread(dll_instance_hdr->file_handler, dll_instance_hdr->elf_section_header_table_ptr, section_header_table_len, &rd_count);
		if(rd_count != section_header_table_len)
			break;
		if(LOADER_NO_ERROR != loader_load_section_into_memory( dll_instance_hdr))
			{
				DLL_TRACE("load sections into memory failed\n");
				break;
			}
		if(LINKER_NO_ERROR != linker_link_sections_in_memory( dll_instance_hdr))
			{
				DLL_TRACE("link sections in the memory failed\n");
				break;
			}
		return dll_instance_hdr;
	}while(0);
	dll_fclose(dll_instance_hdr->file_handler);
	GLOBAL_FREE(dll_instance_hdr);
	DLL_TRACE("---load dll failed---\n");
	return NULL;

}

DLL_INSTANCE_HANDLER GetModuleHandle(WCHAR* lpModuleName)
{
	return NULL;
}
BOOL FreeLibrary(DLL_INSTANCE_HANDLER hModule)
{
	if(hModule == NULL)
	{
		DLL_TRACE("dll has been freed\n");
		return FALSE;
	}
	dll_fclose(hModule->file_handler );
	GLOBAL_FREE(hModule->dll_memory_base_ptr);
	GLOBAL_FREE(hModule->elf_section_header_table_ptr);
	GLOBAL_FREE(hModule->loader_table_ptr);
	GLOBAL_FREE(hModule);
	return TRUE;
}

FARPROC GetProcAddress(DLL_INSTANCE_HANDLER hModule,char* lpProcName)
{
	return (FARPROC)linker_get_symbol_addr( hModule, lpProcName);
}
FARVAR  GetVarAddress(DLL_INSTANCE_HANDLER hModule,char* lpVarName)
{
	return (FARVAR)linker_get_symbol_addr( hModule, lpVarName);
}


DWORD 	GetModuleFileName(DLL_INSTANCE_HANDLER hModule, WCHAR* lpFilename, DWORD nSize)
{
	if(NULL == hModule)
	{
		return 0;
	}
	else
	{
		dll_wcsncpy(lpFilename, hModule->dll_file_path,nSize);
	}
	return dll_wcslen(hModule->dll_file_path);
}




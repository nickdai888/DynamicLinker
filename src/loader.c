
#include "..\inc\loader.h"
#include "..\inc\plt_lyr.h"
#include "..\inc\dyn_prot.h"
#include "..\inc\interface.h"

/**********************************************************
* get memoey section count ,获取需要存放到内存中的section 数量
*此函数必需和loader_alloc_section_space()中的匹配 否则会引起内存方面的问题
***********************************************************/
static Elf32_Word 
_loader_get_elf_memory_number(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	int idx =0;
	Elf32_Word number = 0;
	Elf32_Shdr *section_ptr = dll_instance_hdr->elf_section_header_table_ptr;
	if(section_ptr == NULL)
		return 0;
	for( idx=0; idx < dll_instance_hdr->elf_headr.e_shnum; idx++,section_ptr++ )
	{
		if( ((section_ptr->sh_flags == (SHF_ALLOC + SHF_EXECINSTR)) &&(section_ptr->sh_type == SHT_PROGBITS))||
			((section_ptr->sh_flags == (SHF_ALLOC + SHF_WRITE)) &&(section_ptr->sh_type == SHT_PROGBITS) )||
			((section_ptr->sh_flags == (SHF_ALLOC + SHF_WRITE)) &&(section_ptr->sh_type == SHT_NOBITS))||
			((section_ptr->sh_flags ==  SHF_ALLOC) &&(section_ptr->sh_type == SHT_PROGBITS) ) )
			{
				number++;
			}
	}
	return number;
}

//API for get the number of section program has
Elf32_Word 
loader_get_elf_memory_number(void* dll_instance_hdr)
{
	return _loader_get_elf_memory_number(dll_instance_hdr);
}


#define _SECTION_INFOMATION_COPY_ \
loader_record_ptr->section_idx = section_idx;\
loader_record_ptr->sh_file_offset = section_header_ptr->sh_offset;\
loader_record_ptr->section_size = section_header_ptr->sh_size;  \
loader_record_ptr->sh_addralign = section_header_ptr->sh_addralign;\
loader_record_ptr->sh_type = section_header_ptr->sh_type;\
if(((int)current_memory_ptr%SECTION_ALIGN_BYTES) != 0)\
{\
	current_memory_ptr += SECTION_ALIGN_BYTES - (Elf32_Word)current_memory_ptr%SECTION_ALIGN_BYTES;\
}\
loader_record_ptr->section_base_address = (Elf32_Addr)current_memory_ptr;\
current_memory_ptr += loader_record_ptr->section_size;\
loader_record_ptr++;

/*static :_loader_prepare_before_load
* prepare some infomation before loading the section into memory,just like create loader table(mem mapping of sections).
*/
static LOADER_OPER_ERR 
_loader_prepare_before_load(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	Elf32_Word mem_section_num;
	int section_idx = 0;
	Elf32_Shdr *section_header_ptr = NULL;
	char *current_memory_ptr = NULL;
	Elf32_Loader_Record *loader_record_ptr = NULL;
	mem_section_num = _loader_get_elf_memory_number(dll_instance_hdr);
	if(mem_section_num == 0)//no section to be load
		return LOADER_ELF_NO_SETCTION_LOAD;
	dll_instance_hdr->loader_table_ptr = (Elf32_Loader_Record*)GLOBAL_MALLOC(mem_section_num * sizeof(Elf32_Loader_Record));
	if( dll_instance_hdr->loader_table_ptr == NULL)
		{
			  return LOADER_ELF_INTO_MEM_FAILED;
		}
	else
		{
		 	dll_memset(dll_instance_hdr->loader_table_ptr ,  0, mem_section_num * sizeof(Elf32_Loader_Record));
		}
	//build the section mapping info in the memory
	
	loader_record_ptr = dll_instance_hdr->loader_table_ptr;
	section_header_ptr = dll_instance_hdr->elf_section_header_table_ptr;

	//.CODE
	for( section_idx=0; section_idx<(int)dll_instance_hdr->elf_headr.e_shnum; section_idx++,section_header_ptr++ )
	{
		if( (section_header_ptr->sh_flags == (SHF_ALLOC + SHF_EXECINSTR)) &&
			(section_header_ptr->sh_type == SHT_PROGBITS))
		{
			 _SECTION_INFOMATION_COPY_
		 	 DLL_TRACE("----------1)-load section id: %d into mem <%d> bytes---------------\n",section_idx,(loader_record_ptr - 1)->section_size);
		}
	}
	
	//.RODATA
	section_header_ptr =  dll_instance_hdr->elf_section_header_table_ptr;;
	for( section_idx=0; section_idx<(int)dll_instance_hdr->elf_headr.e_shnum; section_idx++,section_header_ptr++ )
	{
		if( (section_header_ptr->sh_flags == SHF_ALLOC) &&
			(section_header_ptr->sh_type == SHT_PROGBITS) )
		{
			_SECTION_INFOMATION_COPY_
			DLL_TRACE("----------2)-load section id: %d into mem <%d> bytes---------------\n",section_idx,(loader_record_ptr - 1)->section_size);
			
		}
	}
	//.RWDATA
	section_header_ptr =  dll_instance_hdr->elf_section_header_table_ptr;;
	for( section_idx=0; section_idx<(int)dll_instance_hdr->elf_headr.e_shnum; section_idx++,section_header_ptr++ )
	{
		if( (section_header_ptr->sh_flags == (SHF_ALLOC + SHF_WRITE)) &&
			(section_header_ptr->sh_type == SHT_PROGBITS) )
		{
			_SECTION_INFOMATION_COPY_
			DLL_TRACE("---------3)--load section id: %d into mem <%d> bytes---------------\n",section_idx,(loader_record_ptr - 1)->section_size);
			
		}
	}

	//.BSS
	section_header_ptr =  dll_instance_hdr->elf_section_header_table_ptr;;
	for( section_idx=0; section_idx<(int)dll_instance_hdr->elf_headr.e_shnum; section_idx++,section_header_ptr++ )
	{
		if( (section_header_ptr->sh_flags == (SHF_ALLOC + SHF_WRITE)) &&
			(section_header_ptr->sh_type == SHT_NOBITS))
		{
			_SECTION_INFOMATION_COPY_
			DLL_TRACE("---------4)--load section id: %d into mem <%d> bytes---------------\n",section_idx,(loader_record_ptr - 1)->section_size);
				
		}
	}
	
	current_memory_ptr += SECTION_ALIGN_BYTES - (Elf32_Word)current_memory_ptr%SECTION_ALIGN_BYTES;
	//real application len + 256 bytes addition for interval, and veneer's space is allocated here
	dll_instance_hdr->veneer_number = plt_get_host_function_number();
	dll_instance_hdr->dll_memory_size = (unsigned int)current_memory_ptr + 256 + dll_instance_hdr->veneer_number*sizeof(thumb_arm_veneer_stub);
	return LOADER_NO_ERROR;
}


//将文件中的段(数据/代码)加载到内存中
static int 
_loader_load_section_data_into_memory(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	int load_table_idx = 0;
	unsigned int read_bytes = 0;
	Elf32_Loader_Record *load_tb_ptr = NULL;
	int load_table_item = 0; //section count loaded into memory
	int residue = 0;//余数
	//------------------------variable------------------------//
	//256 bytes的空间作为缓冲字节
	dll_instance_hdr->dll_memory_base_ptr = (void *)GLOBAL_MALLOC(dll_instance_hdr->dll_memory_size);
	if(dll_instance_hdr->dll_memory_base_ptr  == NULL)
	{
		DLL_TRACE("Error:cannot get the memory space<loader_load_section_data_into_memory()>\n");
		return LOADER_MEMORY_ALLOC_FAILE;
	}
	else
	{
		dll_memset(dll_instance_hdr->dll_memory_base_ptr,0,dll_instance_hdr->dll_memory_size );
	}
	//the last mem part reserved for veneer stub
	dll_instance_hdr->veneer_table = (thumb_arm_veneer_stub*)((UINT)dll_instance_hdr->dll_memory_base_ptr + dll_instance_hdr->dll_memory_size - dll_instance_hdr->veneer_number * sizeof(thumb_arm_veneer_stub));
	if((residue = (unsigned int)dll_instance_hdr->veneer_table%SECTION_ALIGN_BYTES) != 0)
	{
		dll_instance_hdr->veneer_table -= residue; //修正veneer 的location, 字节对其
	}
	//assurance the base address is aligned, not adjust the process beginning memory
	if(((Elf32_Word)dll_instance_hdr->dll_memory_base_ptr%SECTION_ALIGN_BYTES) != 0)
	{
		GLOBAL_FREE(dll_instance_hdr->dll_memory_base_ptr);
		dll_instance_hdr->dll_memory_base_ptr = NULL;
		return LOADER_ADDR_BASE_NOT_ALIGN;
	}
	load_tb_ptr = dll_instance_hdr->loader_table_ptr;
	load_table_item = _loader_get_elf_memory_number(dll_instance_hdr);
	for( load_table_idx = 0; load_table_idx < load_table_item; load_table_idx++)
	{
		//add the offset firstly
		(Elf32_Addr)load_tb_ptr->section_base_address += (Elf32_Addr)dll_instance_hdr->dll_memory_base_ptr;
		if(load_tb_ptr->sh_type != SHT_NOBITS)// assurance once again
		{
			dll_fseek(dll_instance_hdr->file_handler ,load_tb_ptr->sh_file_offset, DLL_FS_FILE_BEGIN );
			dll_fread(dll_instance_hdr->file_handler , (void*)load_tb_ptr->section_base_address, load_tb_ptr->section_size, &read_bytes);
		}
		load_tb_ptr++;
	}
	
	DLL_TRACE("load the program into memory successfully\n");
	return LOADER_NO_ERROR;
}


//get section address in memory by section_id
Elf32_Addr 
loader_get_section_memory_addr(DLL_INSTANCE_HANDLER dll_instance_hdr, int section_id)
{
	int loc_section_id = 0;
	Elf32_Loader_Record * table_ptr = NULL;
	int mem_section_count = 0;
	mem_section_count = _loader_get_elf_memory_number( dll_instance_hdr);
	table_ptr = dll_instance_hdr->loader_table_ptr;
	for( loc_section_id = 0; loc_section_id < mem_section_count; loc_section_id++,table_ptr++ )
	{
		if((int)table_ptr->section_idx == section_id)
		{
			return table_ptr->section_base_address;
		}
	}
	return 0;
}

LOADER_OPER_ERR  
loader_load_section_into_memory(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	int error_code  = LOADER_NO_ERROR;
	Elf32_Word section_count = 0;
	error_code = _loader_prepare_before_load(dll_instance_hdr);
	if(LOADER_NO_ERROR == error_code)
		{
			error_code = _loader_load_section_data_into_memory(dll_instance_hdr);
		}
	section_count = loader_get_elf_memory_number(dll_instance_hdr);
	DLL_TRACE("we have %d sections in memory\n",section_count);
	return error_code;
}


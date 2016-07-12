/*
  This file is part of dll interface module, all the functions are similar with windows DLL API.
*/
#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "dyn_prot.h"
#include "loader.h"
#include "plt_lyr.h"
#include "arm_elf.h"
#include "linker.h"



#define MAX_FILE_PATH_LEN 128
typedef struct DLL_INSTANCE
{
	WCHAR dll_file_path[MAX_FILE_PATH_LEN];
	FS_HANDLE file_handler;
	Elf32_Ehdr   elf_headr;
	Elf32_Shdr *elf_section_header_table_ptr;
	Elf32_Loader_Record *loader_table_ptr;
	void *dll_memory_base_ptr; 	// application loaded base address
	UINT  dll_memory_size;
	thumb_arm_veneer_stub *veneer_table;
	UINT veneer_number;
}*DLL_INSTANCE_HANDLER;

DLL_INSTANCE_HANDLER LoadLibrary(WCHAR *lpLibrary_name);
DLL_INSTANCE_HANDLER GetModuleHandle(WCHAR* lpModuleName);
BOOL 	FreeLibrary(DLL_INSTANCE_HANDLER hModule);
FARPROC GetProcAddress(DLL_INSTANCE_HANDLER hModule,char* lpProcName);
FARVAR  GetVarAddress(DLL_INSTANCE_HANDLER hModule,char* lpVarName);
DWORD 	GetModuleFileName(DLL_INSTANCE_HANDLER hModule, WCHAR* lpFilename, DWORD nSize);

#endif


#ifndef __LOADER_H__
#define __LOADER_H__
#include "arm_elf.h"

#define SECTION_ALIGN_BYTES 4  

typedef enum 
{
	LOADER_NO_ERROR = 0, 
	LOADER_ADDR_BASE_NOT_ALIGN,
	LOADER_MEMORY_ALLOC_FAILE,
	LOADER_ELF_FILE_READ_ERR,
	LOADER_ELF_NO_SETCTION_LOAD,
	LOADER_ELF_INTO_MEM_FAILED
}LOADER_OPER_ERR;

//loader record table,record the loader 
typedef struct{
	Elf32_Word section_idx;
	Elf32_Addr section_base_address;  ///memory address
	Elf32_Word section_size;
	Elf32_Word sh_addralign;
	Elf32_Word sh_file_offset;
	//Elf32_Word sh_flag;  // DEL BY NICK 20090611
	Elf32_Word sh_type;
}Elf32_Loader_Record;

Elf32_Word loader_get_elf_memory_number(void* dll_instance_hdr);
#endif


#include "..\inc\linker.h"
#include "..\inc\dyn_prot.h"
#include "..\inc\interface.h"
#include "..\inc\plt_res.h"
#include "..\inc\plt_lyr.h"

#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_ 
static FS_HANDLE log_handler = NULL;
#endif
extern Elf32_Addr loader_get_section_memory_addr(DLL_INSTANCE_HANDLER dll_instance_hdr, int section_id);

arm_reloc_status_type linker_elf_generic_reloc (void)
{
	return arm_reloc_ok;
}

/*---------------------howto definition begin---------------*/

static reloc_howto_type elf32_arm_howto_table_1[] =
{
	/* No relocation */
	HOWTO (R_ARM_NONE,		/* type */
		0,			/* rightshift */
		0,			/* size (0 = byte, 1 = short, 2 = long) */
		0,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_NONE",		/* name */
		FALSE,			/* partial_inplace */
		0,			/* src_mask */
		0,			/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_PC24,		/* type */
		2,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		24,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_PC24",		/* name */
		FALSE,			/* partial_inplace */
		0x00ffffff,		/* src_mask */
		0x00ffffff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		/* 32 bit absolute */
		HOWTO (R_ARM_ABS32,		/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		32,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ABS32",		/* name */
		FALSE,			/* partial_inplace */
		0xffffffff,		/* src_mask */
		0xffffffff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		/* standard 32bit pc-relative reloc */
		HOWTO (R_ARM_REL32,		/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		32,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_REL32",		/* name */
		FALSE,			/* partial_inplace */
		0xffffffff,		/* src_mask */
		0xffffffff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		/* 8 bit absolute - R_ARM_LDR_PC_G0 in AAELF */
		HOWTO (R_ARM_LDR_PC_G0,	/* type */
		0,			/* rightshift */
		0,			/* size (0 = byte, 1 = short, 2 = long) */
		32,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_LDR_PC_G0",     /* name */
		FALSE,			/* partial_inplace */
		0xffffffff,		/* src_mask */
		0xffffffff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		/* 16 bit absolute */
		HOWTO (R_ARM_ABS16,		/* type */
		0,			/* rightshift */
		1,			/* size (0 = byte, 1 = short, 2 = long) */
		16,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ABS16",		/* name */
		FALSE,			/* partial_inplace */
		0x0000ffff,		/* src_mask */
		0x0000ffff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		/* 12 bit absolute */
		HOWTO (R_ARM_ABS12,		/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		12,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ABS12",		/* name */
		FALSE,			/* partial_inplace */
		0x00000fff,		/* src_mask */
		0x00000fff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_THM_ABS5,	/* type */
		6,			/* rightshift */
		1,			/* size (0 = byte, 1 = short, 2 = long) */
		5,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_THM_ABS5",	/* name */
		FALSE,			/* partial_inplace */
		0x000007e0,		/* src_mask */
		0x000007e0,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		/* 8 bit absolute */
		HOWTO (R_ARM_ABS8,		/* type */
		0,			/* rightshift */
		0,			/* size (0 = byte, 1 = short, 2 = long) */
		8,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_bitfield,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ABS8",		/* name */
		FALSE,			/* partial_inplace */
		0x000000ff,		/* src_mask */
		0x000000ff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_SBREL32,		/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		32,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_SBREL32",	/* name */
		FALSE,			/* partial_inplace */
		0xffffffff,		/* src_mask */
		0xffffffff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_THM_CALL,	/* type */
		1,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		25,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_THM_CALL",	/* name */
		FALSE,			/* partial_inplace */
		0x07ff07ff,		/* src_mask */
		0x07ff07ff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		HOWTO (R_ARM_THM_PC8,	        /* type */
		1,			/* rightshift */
		1,			/* size (0 = byte, 1 = short, 2 = long) */
		8,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_THM_PC8",	/* name */
		FALSE,			/* partial_inplace */
		0x000000ff,		/* src_mask */
		0x000000ff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		HOWTO (R_ARM_BREL_ADJ,	/* type */
		1,			/* rightshift */
		1,			/* size (0 = byte, 1 = short, 2 = long) */
		32,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_BREL_ADJ",	/* name */
		FALSE,			/* partial_inplace */
		0xffffffff,		/* src_mask */
		0xffffffff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_SWI24,		/* type */
		0,			/* rightshift */
		0,			/* size (0 = byte, 1 = short, 2 = long) */
		0,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_SWI24",		/* name */
		FALSE,			/* partial_inplace */
		0x00000000,		/* src_mask */
		0x00000000,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_THM_SWI8,	/* type */
		0,			/* rightshift */
		0,			/* size (0 = byte, 1 = short, 2 = long) */
		0,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_SWI8",		/* name */
		FALSE,			/* partial_inplace */
		0x00000000,		/* src_mask */
		0x00000000,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		/* BLX instruction for the ARM.  */
		HOWTO (R_ARM_XPC25,		/* type */
		2,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		25,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_XPC25",		/* name */
		FALSE,			/* partial_inplace */
		0x00ffffff,		/* src_mask */
		0x00ffffff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		/* BLX instruction for the Thumb.  */
		HOWTO (R_ARM_THM_XPC22,	/* type */
		2,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		22,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_signed,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_THM_XPC22",	/* name */
		FALSE,			/* partial_inplace */
		0x07ff07ff,		/* src_mask */
		0x07ff07ff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		
		HOWTO (R_ARM_ALU_PCREL7_0,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		12,			/* bitsize */
		TRUE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ALU_PCREL_7_0",	/* name */
		FALSE,			/* partial_inplace */
		0x00000fff,		/* src_mask */
		0x00000fff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		HOWTO (R_ARM_ALU_PCREL15_8,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		12,			/* bitsize */
		TRUE,			/* pc_relative */
		8,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ALU_PCREL_15_8",/* name */
		FALSE,			/* partial_inplace */
		0x00000fff,		/* src_mask */
		0x00000fff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		HOWTO (R_ARM_ALU_PCREL23_15,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		12,			/* bitsize */
		TRUE,			/* pc_relative */
		16,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ALU_PCREL_23_15",/* name */
		FALSE,			/* partial_inplace */
		0x00000fff,		/* src_mask */
		0x00000fff,		/* dst_mask */
		TRUE),			/* pcrel_offset */
		
		HOWTO (R_ARM_LDR_SBREL_11_0,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		12,			/* bitsize */
		FALSE,			/* pc_relative */
		0,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_LDR_SBREL_11_0",/* name */
		FALSE,			/* partial_inplace */
		0x00000fff,		/* src_mask */
		0x00000fff,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_ALU_SBREL_19_12,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		8,			/* bitsize */
		FALSE,			/* pc_relative */
		12,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ALU_SBREL_19_12",/* name */
		FALSE,			/* partial_inplace */
		0x000ff000,		/* src_mask */
		0x000ff000,		/* dst_mask */
		FALSE),		/* pcrel_offset */
		
		HOWTO (R_ARM_ALU_SBREL_27_20,	/* type */
		0,			/* rightshift */
		2,			/* size (0 = byte, 1 = short, 2 = long) */
		8,			/* bitsize */
		FALSE,			/* pc_relative */
		20,			/* bitpos */
		complain_overflow_dont,/* complain_on_overflow */
		linker_elf_generic_reloc,	/* special_function */
		"R_ARM_ALU_SBREL_27_20",/* name */
		FALSE,			/* partial_inplace */
		0x0ff00000,		/* src_mask */
		0x0ff00000,		/* dst_mask */
		FALSE),		/* pcrel_offset */
	};

//veneer generator fuction preparation, for mallocation
static BOOL 
_linker_generate_thumb_arm_veneer(DLL_INSTANCE_HANDLER dll_instance_hdr, struct Sym_Info  *symbol_item_info)
{
	int veneer_count = dll_instance_hdr->veneer_number;
	int index = 0;
	thumb_arm_veneer_stub *veneer_stub  = dll_instance_hdr->veneer_table;
	if(symbol_item_info ==NULL ||symbol_item_info->sym_type == NO_INST)
		return FALSE;
	for(index = 0; index < veneer_count, veneer_stub->sym_name != 0; index++,veneer_stub++)  //search the strub firstly
	{
		if(0 == dll_strcmp(veneer_stub->sym_name, symbol_item_info->sym_name))
		{
		 #if DLL_THUMB_SUPPORT
		 //the type may be data,not only code type
		 #if 0
				symbol_item_info->sym_type = THUMB_INST;
		 #endif
				symbol_item_info->sym_addr = &veneer_stub->veneer_object.tbx_inst;
				return TRUE;			
		 #else
		 	{
		 		symbol_item_info->sym_type = ARM_INST;
				symbol_item_info->sym_addr = &veneer_stub->veneer_object.ldr_inst;
				return TRUE;			
		 	}
		 #endif
		}
	}
	if(index == veneer_count)//did't get the veneer, so must generate it
	{
		DLL_TRACE("all veneers is generated, but find none\n");
		return FALSE;
	}
	else
	{
	#if DLL_THUMB_SUPPORT
		veneer_stub->sym_name = symbol_item_info->sym_name;
	//first generate thumb instruction
		veneer_stub->veneer_object.tbx_inst = 0x4778; //thumb "BX PC" instruction
		veneer_stub->veneer_object.tnop_inst = 0x46c0; // thumb NOP instruction 
	//second generate ARM  intruction
		veneer_stub->veneer_object.ldr_inst = 0xe59fc000;
		veneer_stub->veneer_object.bx_inst = 0xe12fff1c;
		veneer_stub->veneer_object.dcd_inst = (int)symbol_item_info->sym_addr;
		if(symbol_item_info->sym_type == THUMB_INST)
		{
			veneer_stub->veneer_object.dcd_inst |= 0x01;
		}
		symbol_item_info->sym_type = THUMB_INST;
		symbol_item_info->sym_addr = &veneer_stub->veneer_object.tbx_inst;
		(Elf32_Sword)symbol_item_info->sym_addr &= 0xfffffffe;	//assurance the addr is 2 aligned 
		veneer_stub = NULL;
		return TRUE;	
	#else
		DLL_TRACE("not find veneer, thus will create one\n");
		//veneer location is: veneer_stub now
		veneer_stub->sym_name = symbol_item_info->sym_name;
		veneer_stub->veneer_object.ldr_inst = 0xe59fc000;
		veneer_stub->veneer_object.bx_inst = 0xe12fff1c;
		veneer_stub->veneer_object.dcd_inst = (int)symbol_item_info->sym_addr;
		if(symbol_item_info->sym_type == THUMB_INST)
		{
			veneer_stub->veneer_object.dcd_inst |= 0x01;
		}
		symbol_item_info->sym_type = ARM_INST;
		symbol_item_info->sym_addr = &veneer_stub->veneer_object.ldr_inst;
		(Elf32_Sword)symbol_item_info->sym_addr &= 0xfffffffc;	//assurance the addr is 4 aligned 
		veneer_stub = NULL;
		return TRUE;	
	#endif
	}
	return FALSE;
}

/*------------------howto definition end------------------*/

  void  _linker_arm_putl16 (unsigned short data, Elf32_Word p)
  {
	  char *addr = (char *)p;
	  addr[0] = data & 0xff;
	  addr[1] = (data >> 8) & 0xff;
  }
  
  void _linker_arm_putl32 (unsigned int data, Elf32_Word p)
  {
	  char *addr = (char *)p;
	  addr[0] = data & 0xff;
	  addr[1] = (data >>  8) & 0xff;
	  addr[2] = (data >> 16) & 0xff;
	  addr[3] = (data >> 24) & 0xff;
  }
  
  
  void _linker_arm_putl8 (unsigned char data, Elf32_Word p)
  {
	  unsigned char *addr = (unsigned char *)p;
	  addr[0] = data;
  }

  unsigned char _linker_arm_get8(Elf32_Word p)
 {
		 const char *addr = (char *)p;
	 return addr[0];
  }
  
  unsigned short _linker_arm_getl16 (Elf32_Word p)
  {
	  const char *addr = (char *)p;
	  return (addr[1] << 8) | addr[0];
  }
  
  unsigned int _linker_arm_getl32 ( Elf32_Word p)
  {
	  const char *addr = (char *)p;
	  unsigned int v;
	  v = (unsigned long) addr[0];
	  v |= (unsigned long) addr[1] << 8;
	  v |= (unsigned long) addr[2] << 16;
	  v |= (unsigned long) addr[3] << 24;
	  return v;
  }

#define GET8(P)  _linker_arm_get8(P)
#define PUT8(P,D)  _linker_arm_putl8(D,P)

#define GET16(P)  _linker_arm_getl16(P)
#define PUT16(P,D)  _linker_arm_putl16(D,P)

#define GET32(P)  _linker_arm_getl32(P)
#define PUT32(P,D)  _linker_arm_putl32(D,P)



/***************************************************************************************
*linker_get_symbol_item_by_sectionId
*dll_instance_hdr: dll instance handler
*symbol_section_id: symbol section id 
*symbol_index: the item index in the symbol section
*****************************************************************************************/
static int 
_linker_get_symbol_item_by_sectionId(DLL_INSTANCE_HANDLER dll_instance_hdr, int symbol_section_id,int symbol_index,Elf32_Sym *symbol_item)
{
	Elf32_Shdr *section_header_ptr = NULL;
	int section_offset = 0;
	unsigned int rd_bytes = 0; 
	section_header_ptr = dll_instance_hdr->elf_section_header_table_ptr + symbol_section_id;
	section_offset =  symbol_index * sizeof(Elf32_Sym);
	dll_fseek( dll_instance_hdr->file_handler,  section_header_ptr->sh_offset + section_offset, DLL_FS_FILE_BEGIN );
	dll_fread( dll_instance_hdr->file_handler,  symbol_item, sizeof(Elf32_Sym), &rd_bytes );
	if(rd_bytes != sizeof(Elf32_Sym))
	{
		return LINKER_GET_SYMBOL_ITEM_FAILED;
	}
	return LINKER_NO_ERROR;
}

static char string_buffer[MAX_SYM_NAME_LEN];//used for storing searching result
static char* 
_linker_elf_get_string(DLL_INSTANCE_HANDLER dll_instance_hdr,Elf32_Shdr* strings, int offset)
{
	unsigned int rd_bytes = 0;
	dll_memset(string_buffer,0,sizeof(string_buffer));
	dll_fseek( dll_instance_hdr->file_handler, strings->sh_offset + offset, DLL_FS_FILE_BEGIN );
	dll_fread( dll_instance_hdr->file_handler,string_buffer,sizeof(string_buffer),&rd_bytes);
	return string_buffer;
}

static Elf32_Shdr* 
_linker_info_get_shstrtab(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	return (Elf32_Shdr*)(dll_instance_hdr->elf_section_header_table_ptr + dll_instance_hdr->elf_headr.e_shstrndx);
}

static Elf32_Shdr* 
_linker_elf_find_section_name(DLL_INSTANCE_HANDLER dll_instance_hdr, char* name)
{
	int i = 0;
	Elf32_Shdr* first = dll_instance_hdr->elf_section_header_table_ptr;
	Elf32_Shdr* shstrtab = _linker_info_get_shstrtab(dll_instance_hdr);
	
	for( i = 0; i < dll_instance_hdr->elf_headr.e_shnum; i++,first++ )
	{
		if( 0 == dll_strcmp( _linker_elf_get_string(dll_instance_hdr, shstrtab, first->sh_name), name))
		{
			return first;
		}
	}
	return NULL;
}

// here it is how to find symbol name by symbol
static char* 
_linker_elf_get_symbol_name(DLL_INSTANCE_HANDLER dll_instance_hdr, const Elf32_Sym* sym)
{
	Elf32_Shdr* string_tab = NULL;
	if(NULL == sym )
	{
		return NULL;
	}
	//get string table header address
	string_tab = _linker_elf_find_section_name(dll_instance_hdr,".strtab");
	if(NULL == string_tab)
	{
		return NULL;
	}
	return _linker_elf_get_string(dll_instance_hdr,string_tab, sym->st_name);
}

#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_ 
static char dll_symbol_string[_DLL_MAX_OBJECT_SYMBOL_COUNT_][200];
//if the return is negative, then the string is not in the buffer. the target string is added into buffer automaticly.
 int _linker_is_string_added(char *string)
{
	static int  index = 0;
	int cusor = 0;
	if(NULL == string)
	return -1;
	for(cusor = 0; cusor < index ; cusor++)
	{
		if(dll_strcmp(string, dll_symbol_string[cusor]) == 0)
			return cusor;
	}
	dll_strcpy(dll_symbol_string[index],string);
	index++;
	return -1;
}
#endif

/*************************************************************
*there are two probability: the symbol is defined in the host,thus we can get the position and type
*of the symbol we need from external medium; the symbol is defined in the obj file,and we 
*can get the position of it from elf file infomation.
***************************************************************/
static void 
_linker_get_symbol_info(DLL_INSTANCE_HANDLER dll_instance_hdr,const Elf32_Sym *sym_item, struct Sym_Info *symbol_item_info)
{
	//accelorate the seaching speed
	Elf32_Word section_idx = 0;
	Elf32_Addr symbol_addr = 0;
	
	if(NULL == sym_item)
	{
		return;
	}
	dll_memset( symbol_item_info, 0,sizeof(struct Sym_Info) );
	if(sym_item->st_shndx != SHN_UNDEF)  //inner defined
	{
		section_idx = sym_item->st_shndx;
		symbol_addr = loader_get_section_memory_addr(dll_instance_hdr,section_idx);
		symbol_addr += sym_item->st_value; //base address + offset
		symbol_item_info->sym_addr = (void*)symbol_addr;
		#if DLL_THUMB_SUPPORT
		//symbol_item_info->sym_type = THUMB_INST;
		#endif
	}
	else  //outside defined,the symbol is defined outside of the object file, for us now ,it is defined in the host,MTK platform for example. 
	{	
		char * symbol_name = _linker_elf_get_symbol_name(dll_instance_hdr, sym_item);
		if(NULL == symbol_name)
		{
			DLL_TRACE(" --------------warning: symbol name get failed------------\n ");
			return ;
		}
		#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_ 
			{
				//help generation of plt_res.h
				char wr_string[256];
				UINT wrlen = 0;
				if(_linker_is_string_added(symbol_name) < 0)
				{
					dll_memset(wr_string,0,sizeof(wr_string));
					dll_fseek(log_handler,0,DLL_FS_FILE_END);
					dll_strcpy(wr_string,symbol_name);
					dll_strcat(wr_string,"\n");
					dll_fwrite(log_handler, wr_string, dll_strlen(wr_string), &wrlen);
				}
			}
		#endif
		
		plt_get_host_symbol_info(symbol_name,symbol_item_info);
		//if it is function.firstly get veneer, if the veneer is not exist, generate it 
		if(symbol_item_info->sym_type != NO_INST)
		{
			if(!_linker_generate_thumb_arm_veneer( dll_instance_hdr,  symbol_item_info))//symbol_item_info has contained the veneer infomation
			{
				DLL_TRACE("cannot generate veneer\n");
			}
		}
	}
	return;
}

/*
*@function: _linker_elf32_arm_howto_from_type
*
*/
static reloc_howto_type *  
_linker_elf32_arm_howto_from_type (unsigned int r_type)
  {
  	int index = 0;
	int rel_type_count = 0;
	rel_type_count = NUM_ELEM (elf32_arm_howto_table_1);
	for(index = 0; index <  rel_type_count; index++)
		{
			if(elf32_arm_howto_table_1[index].type == r_type)
				{
					return &elf32_arm_howto_table_1[index];
				}
		}
	  return NULL;
  }

unsigned int
_linker_get_reloc_size (reloc_howto_type *howto)
{
	  switch (howto->size)
	    {
		    case 0: 
				return 1;
		    case 1: 
				return 2;
		    case 2: 
				return 4;
		    case 3: 
				return 0;
		    case 4: 
				return 8;
		    case 8: 
		  		return 16;
		    case -2: 
				return 4;
		    default: 
				return 4;
	    }
}

/* Clear a given location using a given howto, by applying a relocation value
   of zero and discarding any in-place addend.  This is used for fixed-up
   relocations against discarded symbols, to make ignorable debug or unwind
   information more obvious.  */

void
_linker_clear_contents (reloc_howto_type *howto,char *location)
{
  int size;
  bmd_vma x = 0;
  /* Get the value we are going to relocate.  */
  size = _linker_get_reloc_size (howto);
  switch (size)
    {
	   
	case 1:
		x = GET8 ((Elf32_Word)location);
		break;
	case 2:
		x = GET16 ( (Elf32_Word)location);
		break;
	case 4:
		x = GET32 ((Elf32_Word)location);
		break;
	default:
		break;
    }

  /* Zero out the unwanted bits of X.  */
  x &= ~howto->dst_mask;
  /* Put the relocated value back in the object file.  */
  switch (size)
    {
	    case 1:
	      PUT8 ((Elf32_Word)location, x);
	      break;
	    case 2:
	      PUT16((Elf32_Word)location, x);
	      break;
	    case 4:
	      PUT32((Elf32_Word)location, x);
	      break;
	    default:
		break;
    }
}


/* For a given value of n, calculate the value of G_n as required to
   deal with group relocations.  We return it in the form of an
   encoded constant-and-rotation, together with the final residual.  If n is
   specified as less than zero, then final_residual is filled with the
   input value and no further action is performed.  */
static bmd_vma
_linker_calculate_group_reloc_mask (bmd_vma value, int n, bmd_vma *final_residual)
{
  int current_n;
  bmd_vma g_n;
  bmd_vma encoded_g_n = 0;
  bmd_vma residual = value; /* Also known as Y_n.  */

  for (current_n = 0; current_n <= n; current_n++)
    {
      int shift;

      /* Calculate which part of the value to mask.  */
      if (residual == 0)
        shift = 0;
      else
        {
          int msb;

          /* Determine the most significant bit in the residual and
             align the resulting value to a 2-bit boundary.  */
          for (msb = 30; msb >= 0; msb -= 2)
            if (residual & (3 << msb))
              break;

          /* The desired shift is now (msb - 6), or zero, whichever
             is the greater.  */
          shift = msb - 6;
          if (shift < 0)
            shift = 0;
        }

      /* Calculate g_n in 32-bit as well as encoded constant+rotation form.  */
      g_n = residual & (0xff << shift);
      encoded_g_n = (g_n >> shift)
                    | ((g_n <= 0xff ? 0 : (32 - shift) / 2) << 8);

      /* Calculate the residual for the next time around.  */
      residual &= ~g_n;
    }

  *final_residual = residual;

  return encoded_g_n;
}

/* The thumb form of a long branch is a bit finicky, because the offset
   encoding is split over two fields, each in it's own instruction. They
   can occur in any order. So given a thumb form of long branch, and an
   offset, insert the offset into the thumb branch and return finished
   instruction.

   It takes two thumb instructions to encode the target address. Each has
   11 bits to invest. The upper 11 bits are stored in one (identified by
   H-0.. see below), the lower 11 bits are stored in the other (identified
   by H-1).

   Combine together and shifted left by 1 (it's a half word address) and
   there you have it.

     Op: 1111 = F,
     H-0, upper address-0 = 000
     Op: 1111 = F,
     H-1, lower address-0 = 800

   They can be ordered either way, but the arm tools I've seen always put
   the lower one first. It probably doesn't matter. krk@cygnus.com

   XXX:  Actually the order does matter.  The second instruction (H-1)
   moves the computed address into the PC, so it must be the second one
   in the sequence.  The problem, however is that whilst little endian code
   stores the instructions in HI then LOW order, big endian code does the
   reverse.  nickc@cygnus.com.  */

#define LOW_HI_ORDER 0xF800F000
#define HI_LOW_ORDER 0xF000F800

static Elf32_Sword
_linker_insert_thumb_branch (Elf32_Sword br_insn, int rel_off, SYM_TYPE inst_type)
{
  unsigned int low_bits;
  unsigned int high_bits;

  //BFD_ASSERT ((rel_off & 1) != 1);

  rel_off >>= 1;                              /* Half word aligned address.  */
  low_bits = rel_off & 0x000007FF;            /* The bottom 11 bits.  */
  high_bits = (rel_off >> 11) & 0x000007FF;   /* The top 11 bits.  */

  if ((br_insn & LOW_HI_ORDER) == LOW_HI_ORDER)
    br_insn = LOW_HI_ORDER | (low_bits << 16) | high_bits;
  else if ((br_insn & HI_LOW_ORDER) == HI_LOW_ORDER)
    br_insn = HI_LOW_ORDER | (high_bits << 16) | low_bits;
  else
    /* FIXME: the BFD library should never abort except for internal errors
       - it should return an error status.  */
    //abort (); /* Error - not a valid branch instruction form.  */
	DLL_TRACE("-----relocation error--------\n");
  if(inst_type  == ARM_INST)
  	{
  		br_insn &= 0xefffffff; //convert bl to blx
  	}
  return br_insn;
}


/**********************************************************************
*function name: _linker_relocation_execution
*discription: relocation related key execution procedure
*para:
*dll_instance_hdr: dll handler
*apply_address: the address relocation apply
*rel_type: the corresponding relocation type 
*symbol_item_info: the symbol infomation associated to the relocation 
************************************************************************/
static arm_reloc_status_type 
_linker_relocation_execution(DLL_INSTANCE_HANDLER dll_instance_hdr, Elf32_Addr apply_address, unsigned char rel_type, const struct Sym_Info *symbol_item_info)
{
	 reloc_howto_type *howto = NULL;
	 Elf32_Sword apply_data = 0;
	 bmd_vma  addend = 0;
	 bmd_signed_vma  signed_addend = 0;
	 Elf32_Sword byte_offset = 0;

	//------------------local variable-----------------------//
	 howto = _linker_elf32_arm_howto_from_type(rel_type);
	if(NULL == howto)
	{
		return arm_reloc_undefined;
	}
	//get adddend
	 addend = GET32(apply_address) & howto->src_mask;
	 if (addend & ((howto->src_mask + 1) >> 1))
	  {
		  signed_addend = -1;
		  signed_addend &= ~ howto->src_mask;
		  signed_addend |= addend;
	  }
	  else
	  {
		  signed_addend = addend;
	  }

	  switch(rel_type)
  	  {
  		 case R_ARM_NONE:
      		 	return arm_reloc_ok;
      		 	
		  case R_ARM_ABS12:
			  apply_data = (Elf32_Sword)symbol_item_info->sym_addr + addend;
			  if(apply_data > 0xfff)
			  {
				  return arm_reloc_overflow;
			  }
			  apply_data |= GET32(apply_address) & 0xfffff000;
			  PUT32(apply_address, apply_data);
			  break;
			
		  case R_ARM_XPC25:	  /* Arm BLX instruction.  */
		  case R_ARM_PC24:	  /* Arm B/BL instruction */
		  	//// the following arithmetic is based on the linux gdb source
			#if  1
				apply_data = (unsigned long)symbol_item_info->sym_addr - (unsigned long)apply_address;
				apply_data += (signed_addend << howto->size);
				signed_addend = apply_data;
				signed_addend >>= howto->rightshift;
				addend = (apply_data & 2);
				apply_data = (signed_addend & howto->dst_mask)|(GET32 (apply_address) & (~ howto->dst_mask));
				/* Set the H bit in the BLX instruction.  */
				if (symbol_item_info->sym_type == THUMB_INST) //blx thumb instruction
				{
					  if (addend)
					  	{
							apply_data |= (1 << 24);
					  	}
					  else
					  	{
							apply_data &= ~(bmd_vma)(1 << 24);
					  	}
				}
				/*BEGIN:DEL BY NICK 20090531*/
				#if 0
				if(symbol_item_info->sym_type == ARM_INST)
				{
					apply_data &= 0xfffffffc; //the result must be always mutipe of 4.(4 butes aligned)
				}
				else if(symbol_item_info->sym_type == THUMB_INST)
				{
					apply_data |= 0x01;
				}
				#endif
				/*END:DEL BY NICK 20090531*/

			#else
				// the following arithmetic is based on the arm-architecture pdf documents,
				byte_offset = (Elf32_Sword)apply_address + 8;
				byte_offset = (Elf32_Sword)symbol_item_info->sym_addr - byte_offset; 
				if((byte_offset > 33554428)||(byte_offset < -33554432 ))
				{
					 return arm_reloc_overflow;
				}
				/*BEGIN:MOD By Nick 20090528*/
				#if 0
				apply_data =( byte_offset >>2)|0xea000000;
				#endif
				apply_data =( byte_offset >>2 )|(GET32 (apply_address)&(0xff000000)); 
				/*END:MOD By Nick 20090528*/

			#endif
			
		  	PUT32 (apply_address, apply_data);
			return arm_reloc_ok;
			break;
			
			case R_ARM_ABS32:
			  apply_data =(Elf32_Sword)symbol_item_info->sym_addr + addend;
			 if (symbol_item_info->sym_type == THUMB_INST) // thumb instruction address
			 	{
				    apply_data |= 1;
			 	}
			    PUT32 (apply_address, apply_data);
			  break;

			case R_ARM_REL32:
			   apply_data = (Elf32_Sword)symbol_item_info->sym_addr + addend;
			 if (symbol_item_info->sym_type == THUMB_INST) // thumb instruction address
			 	{
				    apply_data |= 1;
			 	}
			    apply_data -= apply_address;
			    PUT32(apply_address, apply_data);
			  break;

			 case R_ARM_ABS8:
			      apply_data = (Elf32_Sword)symbol_item_info->sym_addr + (Elf32_Sword)addend;
			      if ((long) apply_data > 0x7f || (long) apply_data < -0x80)
			      	{
					return arm_reloc_overflow;
			      	}
			      PUT8(apply_address, apply_data);
			   break;

			case R_ARM_ABS16:
			  apply_data = (Elf32_Sword)symbol_item_info->sym_addr + addend;
			  if ((long) apply_data > 0x7fff || (long) apply_data < -0x8000)
			  	{
				return arm_reloc_overflow;
			  	}
			  PUT16(apply_address, apply_data);
			break;

			case R_ARM_THM_ABS5:  //thumb ldr,str
			  /* Support ldr and str instructions for the thumb.  */
			  addend = GET16 (apply_address) & howto->src_mask;
			  addend >>= howto->rightshift;
			  apply_data = (Elf32_Sword)symbol_item_info->sym_addr + addend;
			  /* ??? Isn't value unsigned?  */
			  if ((long) apply_data > 0x1f || (long) apply_data < -0x10)
			  	{
				return arm_reloc_overflow;
			  	}
			  apply_data |= GET16 (apply_address) & 0xf83f;
			  PUT16(apply_address, apply_data);
			  break;

			 case  R_ARM_LDR_PC_G0:  //R_ARM_PC13
			 	{
					bmd_vma insn = GET32 (apply_address);
					bmd_vma pc = apply_address;
					bmd_vma sb = 0; /* See note above.  */
					bmd_vma residual = 0;
					bmd_signed_vma signed_value = 0;
 		        		int group = 0;
					int negative = (insn & (1 << 23)) ? 1 : -1;
					signed_addend = negative * (insn & 0xfff);
					signed_value = (bmd_signed_vma)symbol_item_info->sym_addr - (bmd_signed_vma)pc + (bmd_signed_vma)signed_addend;
					_linker_calculate_group_reloc_mask (linker_abs (signed_value), group - 1, &residual);
				        /* Check for overflow.  */
					if (residual >= 0x1000)
					  {
					        return arm_reloc_overflow;
					  }
				        insn &= 0xff7ff000;
				        if (signed_value >= 0)
			        	 {
				           	insn |= 1 << 23;
			        	 }
				          insn |= residual;
					PUT32 (apply_address, insn);
					break;
			 	}
			 	
			case  R_ARM_SWI24: //not sure of this type
			    apply_data = (Elf32_Sword)symbol_item_info->sym_addr + addend;
			    PUT32 (apply_address, apply_data);
			    break;
			    
			case R_ARM_THM_XPC22://BLX
			case R_ARM_THM_CALL: //R_ARM_THM_PC22  BL
#if 0
			{
				bmd_vma relocation;
				bmd_vma reloc_sign;
				BOOL overflow = FALSE;
				bmd_vma upper_insn = GET16 (apply_address);
				bmd_vma lower_insn  = GET16 (apply_address + 2);
				bmd_signed_vma reloc_signed_max;
				bmd_signed_vma reloc_signed_min;
				bmd_vma check;
				bmd_signed_vma signed_check;
				int bitsize;
				int thumb2 = FALSE;

				/* Fetch the addend.  We use the Thumb-2 encoding (backwards compatible
				with Thumb-1) involving the J1 and J2 bits.  */
				bmd_vma s = (upper_insn & (1 << 10)) >> 10;
				bmd_vma upper = upper_insn & 0x3ff;
				bmd_vma lower = lower_insn & 0x7ff;
				bmd_vma j1 = (lower_insn & (1 << 13)) >> 13;
				bmd_vma j2 = (lower_insn & (1 << 11)) >> 11;
				bmd_vma i1 = j1 ^ s ? 0 : 1;
				bmd_vma i2 = j2 ^ s ? 0 : 1;

				addend = (i1 << 23) | (i2 << 22) | (upper << 12) | (lower << 1);
				/* Sign extend.  */
				addend = (addend | ((s ? 0 : 1) << 24)) - (1 << 24);

				signed_addend = addend;
				if (rel_type == R_ARM_THM_XPC22)
				{
					/* Check for Thumb to Thumb call.  a thumb call a thumb function label*/
					/* FIXME: Should we translate the instruction into a BL
					instruction instead ?  */
					if (symbol_item_info->sym_type == THUMB_INST)
					DLL_TRACE("Warning: Thumb BLX instruction targets thumb function\n");
				}
				else
				{
				      /* If it is not a call to Thumb, assume call to Arm.
				       If it is a call relative to a section name, then it is not a
				       function call at all, but rather a long jump.  Calls through
				       the PLT do not require stubs.  */
				      if((symbol_item_info->sym_type == ARM_INST)&&(symbol_item_info->sym_name != NULL)&&(symbol_item_info->sym_name[0] != 0))//call host api or call arm instruction label
				      {
						Elf32_Sword tmp = 0; 	
						Elf32_Sword ret_offset = 0; 
						/* Convert BL to BLX.  */
						lower_insn = (lower_insn & ~0x1000) | 0x0800;
  					       // if (elf32_thumb_to_arm_stub(info, sym_name, input_bfd, output_bfd, input_section,hit_data, sym_sec, rel->r_offset, signed_addend, value, error_message))
						/* Now go back and fix up the original BL insn to point to here.  */
						ret_offset = 
						/* Address of where the stub is located.  */
						(Elf32_Sword)symbol_item_info->sym_addr
						/* Address of where the BL is located.  */
						- apply_address
						/* Addend in the relocation.  */
						- signed_addend
						/* Biassing for PC-relative addressing.  */
						- 8;
						tmp = GET32(apply_address);	
						PUT32(apply_address, (bmd_vma)_linker_insert_thumb_branch(tmp, ret_offset,symbol_item_info->sym_type));
						return arm_reloc_ok;
  					   
				      }
				     else if((symbol_item_info->sym_type == ARM_INST)&&(symbol_item_info->sym_name != NULL)&&(symbol_item_info->sym_name[0] == 0))//inner object
				     	{
				     		DLL_TRACE("rel_type R_ARM_THM_CALL might be wrong\n");
				     	}
				     else if((symbol_item_info->sym_type == THUMB_INST)&&(symbol_item_info->sym_name != NULL)&&(symbol_item_info->sym_name[0] == 0))//inner object
				      {
				      		lower_insn |= 0x1800;	// Make sure this is a BL. +-4M space address
				      }
				     else if((symbol_item_info->sym_type == THUMB_INST)&&(symbol_item_info->sym_name != NULL)&&(symbol_item_info->sym_name[0] != 0))//call a thumb api function of host
				      {
				     	 	//insert a veneer to assurance a far thumb instruction calling 
				     	 	
						return arm_reloc_ok;
				      }
					
				}
				relocation = (Elf32_Sword)symbol_item_info->sym_addr + signed_addend - apply_address;
				check = relocation >> howto->rightshift;

				/* If this is a signed value, the rightshift just dropped
				leading 1 bits (assuming twos complement).  */
				if ((bmd_signed_vma) relocation >= 0)
				signed_check = check;
				else
				signed_check = check | ~((bmd_vma) -1 >> howto->rightshift);

				/* Calculate the permissable maximum and minimum values for
				this relocation according to whether we're relocating for
				Thumb-2 or not.  */
				bitsize = howto->bitsize;
				if (!thumb2)
				{
					bitsize -= 2;
				}
				reloc_signed_max = ((1 << (bitsize - 1)) - 1) >> howto->rightshift;
				reloc_signed_min = ~reloc_signed_max;

				/* Assumes two's complement.  */
				if (signed_check > reloc_signed_max || signed_check < reloc_signed_min)
				overflow = TRUE;

				if ((lower_insn & 0x1800) == 0x0800)
				/* For a BLX instruction, make sure that the relocation is rounded up
				to a word boundary.  This follows the semantics of the instruction
				which specifies that bit 1 of the target address will come from bit
				1 of the base address.  */
				relocation = (relocation + 2) & ~ 3;

				/* Put RELOCATION back into the insn.  Assumes two's complement.
				We use the Thumb-2 encoding, which is safe even if dealing with
				a Thumb-1 instruction by virtue of our overflow check above.  */
				reloc_sign = (signed_check < 0) ? 1 : 0;
				upper_insn = (upper_insn & ~(bmd_vma) 0x7ff)
				| ((relocation >> 12) & 0x3ff)
				| (reloc_sign << 10);
				lower_insn = (lower_insn & ~(bmd_vma) 0x2fff) 
				| (((!((relocation >> 23) & 1)) ^ reloc_sign) << 13)
				| (((!((relocation >> 22) & 1)) ^ reloc_sign) << 11)
				| ((relocation >> 1) & 0x7ff);

				/* Put the relocated value back in the object file:  */
				PUT16 ( apply_address, upper_insn );
				PUT16 ( apply_address + 2, lower_insn);

				return (overflow ? arm_reloc_overflow : arm_reloc_ok);
			}
		#else
		{
			  Elf32_Sword  inst_offset = 0;
			  Elf32_Sword max_low_offset = -(1<<22);
			  Elf32_Sword max_high_offset = 1<<22 - 2;
			  Elf32_Sword base_address = 0;
			  Elf32_Sword target_address = 0;
			  Elf32_Word upper_insn  = GET16 (apply_address);
			  Elf32_Word lower_insn  =  GET16 (apply_address + 2);
			  base_address = (Elf32_Word)apply_address + 4;
			  target_address =(Elf32_Word)symbol_item_info->sym_addr;
			  if(symbol_item_info->sym_type == ARM_INST)
		  	  { 
		  	  	#if DLL_THUMB_SUPPORT
		  	  		// we do nothing, only ARM v5 above can support blx instruction
				  #else
	  		  		 lower_insn = lower_insn & 0xefff; /* Convert BL to BLX.  */
			 	 #endif
			  }
			  if((lower_insn &0x1000) == 0)//BLX instruction
			  	{
					if(base_address & 0x02) //set bit 1 of the target address to be equal to bit 1 of the base address;
				   target_address |= 0x02;
				else
				  target_address &=(~0x02);
				}
			  inst_offset = target_address - base_address;
			  if((inst_offset > max_high_offset)||(inst_offset < max_low_offset))
			  return arm_reloc_overflow;
			  upper_insn = upper_insn & 0x0000f800;//clear the inst content
			  upper_insn |= 0x000007ff & ((inst_offset<<9)>>21);
			  
			   lower_insn = lower_insn & 0x0000f800;//clear the inst content
			  lower_insn |= 0x000007ff & ((inst_offset<<20)>>21);
			  
			  PUT16 ( apply_address, upper_insn );
			  PUT16 ( apply_address + 2, lower_insn);
			  return arm_reloc_ok;		  
		}
		#endif
			default:
				return arm_reloc_notsupported;

  	  }
	
	return arm_reloc_ok;
}

/**************************************************************************************************************
*A relocation section references two other sections: a symbol table and a section to modify. The section header's
*sh_info and sh_link members, described in section 3.3, Sections, above, specify these relationships.
*dll_instance_hdr:dll instance handler
*rel_section_idx: relocation section id
*rel_entry: the address of the .rel item to be processed
***************************************************************************************************************/
static int 
_linker_rel_one_entry(DLL_INSTANCE_HANDLER dll_instance_hdr, int rel_section_idx, Elf32_Rel *rel_entry)
{
	Elf32_Addr r_offset = 0;
	Elf32_Word r_info = 0;
	Elf32_Word symbol_table_index = 0;
	unsigned char rel_type = 0;
	Elf32_Shdr *rel_section_header_ptr = NULL;
	Elf32_Sym symbol_item;
	Elf32_Addr rel_section_memory_addr = 0;
	arm_reloc_status_type rel_result = 0;
	int sym_section_idx = 0;//refered symbol section 
	int mod_section_idx = 0;//the section id which this rel entry to modify
	Elf32_Addr rel_memory_address = 0;
	struct Sym_Info symbol_item_info;
	
	if(NULL == rel_entry)
		return LINKER_REL_ENTRY_INVALID;

	rel_section_header_ptr = dll_instance_hdr->elf_section_header_table_ptr;
	r_offset = rel_entry->r_offset; //32 bits offset
	r_info = rel_entry->r_info;
	
	rel_type = (unsigned char)r_info;
	symbol_table_index = r_info>>8;//the index of the symbol  in the symbol table
	//get the information of the relocation section
	sym_section_idx = rel_section_header_ptr[rel_section_idx].sh_link;
	mod_section_idx = rel_section_header_ptr[rel_section_idx].sh_info;
	
	if( _linker_get_symbol_item_by_sectionId(dll_instance_hdr, sym_section_idx, symbol_table_index, &symbol_item) !=  LINKER_NO_ERROR )
	{
		DLL_TRACE("cannot get the symbol item section_id:%d, symbol_index:%d \n", sym_section_idx, symbol_table_index);
		return LINKER_READ_SYM_INFO_ERR;
	}
#if _DLL_DEBUG_
	{
		char *sym_name = NULL;
		DLL_TRACE("symbol info:%x\n",symbol_item.st_info);
		sym_name = _linker_elf_get_symbol_name(dll_instance_hdr,&symbol_item);
		DLL_TRACE("symbol name:%s\n",sym_name);
	}
#endif
	rel_section_memory_addr = loader_get_section_memory_addr(dll_instance_hdr, mod_section_idx);
	if( rel_section_memory_addr == 0 )
	{
		DLL_TRACE("cannot get the section base address of section id (%d)\n",mod_section_idx);
		return LINKER_READ_SYM_INFO_ERR;
	}
	rel_memory_address = (Elf32_Addr)(rel_section_memory_addr + r_offset); // address where relocation apply
	 _linker_get_symbol_info(dll_instance_hdr, &symbol_item, &symbol_item_info);
	if(0 == symbol_item_info.sym_addr) //cannot get symbol infomation
	{
		return LINKER_REL_CANNOT_GET_REL_S_VALUE;
	}

	if(arm_reloc_ok != (rel_result = _linker_relocation_execution( dll_instance_hdr, rel_memory_address, rel_type, &symbol_item_info)))
	{
		DLL_TRACE("type <%d> relocation failed: <%d>\n",rel_type,rel_result);
		return LINKER_REL_RELOCATION_OPERATION_FAILED;
	}
	
	return LINKER_NO_ERROR;
}


		


/********************************************************************
*name: linker_rel_section
*dll_instance_hdr : dll instance handler
*section_header_ptr: rel section header ptr
*********************************************************************/
static LINKER_OPER_ERR 
_linker_rel_section(DLL_INSTANCE_HANDLER dll_instance_hdr, int section_id, Elf32_Shdr *section_header_ptr) 
{
	unsigned int rd_bytes = 0;
	int rel_idx = 0;
	Elf32_Rel * rel_section_ptr = NULL;
	int rel_section_count = 0;
	int link_err = LINKER_NO_ERROR;

	if(section_header_ptr->sh_type != SHT_REL)
	{
		return LINKER_SECTION_INVALID;
	}
	rel_section_count = section_header_ptr->sh_size/section_header_ptr->sh_entsize;//comput the relocation number
	rel_section_ptr = (Elf32_Rel *)GLOBAL_MALLOC(section_header_ptr->sh_size);
	if(rel_section_ptr == NULL)
	{
		return LINKER_MEMORY_ALLOC_FAILE;
	}
	else
	{
		dll_memset(rel_section_ptr,0,section_header_ptr->sh_size);
	}
	/*load the .rel section into memory*/
	dll_fseek(dll_instance_hdr->file_handler, section_header_ptr->sh_offset, DLL_FS_FILE_BEGIN );
	dll_fread(dll_instance_hdr->file_handler, (void*)rel_section_ptr, section_header_ptr->sh_size, &rd_bytes);

	if(rd_bytes == (int)section_header_ptr->sh_size)  //assurance the reading action is successful
	{
		for( rel_idx = 0; rel_idx < rel_section_count; rel_idx++)  //relocate item one by one
		{
			//some relocation entry we cannot need relocate it, then report the error to the upper layer
			 if (LINKER_NO_ERROR != (link_err = _linker_rel_one_entry(dll_instance_hdr,section_id, rel_section_ptr + rel_idx )))
			 	{
			 		DLL_TRACE("--------------relocate %d error------------\n", section_id);
					break;
			 	}
		}
	}
	GLOBAL_FREE(rel_section_ptr);
	rel_section_ptr = NULL;
	return link_err;
}
		

/*****************************************************
*function:_linker_get_symbol_by_name
*discription:how to find symbol by symbol name
*assurance that one elf file must have only one .symtab section and one .strtab section, 
* otherwise there will be an error 
******************************************************/
BOOL 
_linker_get_symbol_by_name(DLL_INSTANCE_HANDLER dll_instance_hdlr,char* name,Elf32_Sym *p_sym)
{
	Elf32_Shdr* symtab = NULL;
	Elf32_Shdr* strings_tab = NULL;
	int sym_count = 0;
	int sym_index = 0;
	unsigned int rd_bytes = 0;
	Elf32_Sym sym;
	char *sym_name = NULL;
	
	dll_memset(p_sym,0,sizeof(Elf32_Sym));
	strings_tab = _linker_elf_find_section_name(dll_instance_hdlr,".strtab");
	symtab = _linker_elf_find_section_name(dll_instance_hdlr,".symtab");
	if((NULL == symtab)||(NULL == strings_tab))
	{
		DLL_TRACE("--get symbol table or string tab error--\n");
		return FALSE ;
	}
	sym_count = symtab->sh_size/symtab->sh_entsize;//symbol item number
	for(sym_index = 0; sym_index < sym_count; sym_index++)
	{
		dll_fseek(dll_instance_hdlr->file_handler,symtab->sh_offset + sym_index*sizeof(Elf32_Sym),DLL_FS_FILE_BEGIN);
		dll_fread(dll_instance_hdlr->file_handler,&sym,sizeof(Elf32_Sym),&rd_bytes);
		if(rd_bytes != sizeof(Elf32_Sym))
		{
			break;
		}
		sym_name = _linker_elf_get_string(dll_instance_hdlr, strings_tab, sym.st_name);
		if(0 == dll_strcmp(sym_name, name))
		{
			dll_memcpy(p_sym, &sym, sizeof(Elf32_Sym));
			return TRUE;
		}
	}
	return FALSE;
}



static void *
_linker_get_symbol_address(DLL_INSTANCE_HANDLER dll_instance_hdlr,char* symbol_name)
{
	Elf32_Sym symbol;
	void *rt_symbol_ptr = NULL;
	void * symbol_section_base_ptr = NULL;
	if(NULL == symbol_name)
	{
		DLL_TRACE("function name is invalid\n");
		return NULL;
	}
	if(NULL == _linker_get_symbol_by_name(dll_instance_hdlr, symbol_name, &symbol))
		return NULL;
	if(STB_GLOBAL != symbol.st_info >> 4)
	{
		DLL_TRACE("can only get global symbol from elf\n");
		return NULL;
	}
	symbol_section_base_ptr = (void*)loader_get_section_memory_addr(dll_instance_hdlr, symbol.st_shndx);
	if(NULL == symbol_section_base_ptr)
	{
		DLL_TRACE("cannot get the %s information from the dll\n",symbol_name);
		return NULL;
	}
	(Elf32_Word)rt_symbol_ptr = (Elf32_Word)symbol.st_value + (Elf32_Word)symbol_section_base_ptr;
	return rt_symbol_ptr;
}



void * linker_get_symbol_addr(DLL_INSTANCE_HANDLER dll_instance_hdlr,char* symbol_name)
{
	return _linker_get_symbol_address( dll_instance_hdlr,  symbol_name);
}

extern WCHAR dll_output_file_path[];
LINKER_OPER_ERR  
linker_link_sections_in_memory(DLL_INSTANCE_HANDLER dll_instance_hdr)
{
	int section_idx  = 0;
	Elf32_Shdr *temp_section_ptr = NULL;
	#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_ 
		if(log_handler == NULL)
		{
			log_handler = dll_fopen(dll_output_file_path, DLL_FS_CREATE_ALWAYS);
		}
	     dll_memset(dll_symbol_string, 0, sizeof(dll_symbol_string));
	#endif
	temp_section_ptr = dll_instance_hdr->elf_section_header_table_ptr;
	//get the rel section info
	for( section_idx = 0; section_idx < dll_instance_hdr->elf_headr.e_shnum; section_idx++,temp_section_ptr++ )
	{
		if(temp_section_ptr->sh_type == SHT_REL) //Only support .rel  relocation type
		{
			if( LINKER_NO_ERROR != _linker_rel_section(dll_instance_hdr, section_idx, temp_section_ptr))
			{
				DLL_TRACE(" link %d section failed\n",section_idx);
				return LINKER_OPERATION_ERR;
			}
			else
			{
				DLL_TRACE("--section %d relocated successful--\n ",section_idx);
			}
		}
	}
	#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_ 
	 if(log_handler != NULL)
	 	{
	 		dll_fclose(log_handler );
			log_handler = NULL;
	 	}
	   dll_memset(dll_symbol_string, 0, sizeof(dll_symbol_string));

	#endif
	return LINKER_NO_ERROR;
}






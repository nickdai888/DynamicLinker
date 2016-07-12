#ifndef __LINKER_H__
#define __LINKER_H__
#include "arm_elf.h"
#include "plt_lyr.h"

typedef enum 
{
	 LINKER_NO_ERROR = 0,
	 LINKER_SECTION_INVALID,
	 LINKER_MEMORY_ALLOC_FAILE,
	 LINKER_FILE_READ_ERR ,
	 LINKER_REL_ENTRY_INVALID,
	 LINKER_READ_SYM_INFO_ERR ,
	 LINKER_PARA_ERR ,
	 LINKER_REL_TYPE_NOT_FOUND ,
	 LINKER_REL_ENTRY_NOT_IN_MEMORY,
	 LINKER_REL_CANNOT_GET_REL_S_VALUE,
	 LINKER_REL_LINK_SECTION_FAILED,
	 LINKER_REL_RELOCATION_OPERATION_FAILED,
	 LINKER_GET_SYMBOL_ITEM_FAILED,
	 LINKER_OPERATION_ERR
}LINKER_OPER_ERR;



#define NUM_ELEM(a) ((sizeof (a)) / sizeof ((a)[0]))

/*define relocation supported type infomation*/
#define RELOC_NUMBER(name, number)     name = number,
#define FAKE_RELOC(name, number)    name = number,
#define EMPTY_RELOC(name)     name,

enum LINKER_REL_TYPE 
{
	/* AAELF official names and numbers.  */
	  RELOC_NUMBER (R_ARM_NONE,            	  0)
	  RELOC_NUMBER (R_ARM_PC24,            	   1)   /* deprecated */
	  RELOC_NUMBER (R_ARM_ABS32,           	  2)
	  RELOC_NUMBER (R_ARM_REL32,           	  3)
	  RELOC_NUMBER (R_ARM_LDR_PC_G0,       	  4)
	  RELOC_NUMBER (R_ARM_ABS16,           	  5)
	  RELOC_NUMBER (R_ARM_ABS12,           	  6)
	  RELOC_NUMBER (R_ARM_THM_ABS5,        	  7)
	  RELOC_NUMBER (R_ARM_ABS8,            	  8)
	  RELOC_NUMBER (R_ARM_SBREL32,         	  9)
	  RELOC_NUMBER (R_ARM_THM_CALL,        	 10)
	  RELOC_NUMBER (R_ARM_THM_PC8,         	 11)
	  RELOC_NUMBER (R_ARM_BREL_ADJ,	       	 12)
	  RELOC_NUMBER (R_ARM_SWI24,           	 13)   /* obsolete */
	  RELOC_NUMBER (R_ARM_THM_SWI8,        	 14)   /* obsolete */
	  RELOC_NUMBER (R_ARM_XPC25,           	 15)   /* obsolete */
	  RELOC_NUMBER (R_ARM_THM_XPC22,       	 16)   /* obsolete */
	  /*17~31 reserved to arm linux*/
	  RELOC_NUMBER (R_ARM_ALU_PCREL7_0,    	 32)   /* obsolete */
	  RELOC_NUMBER (R_ARM_ALU_PCREL15_8,   	 33)   /* obsolete */
	  RELOC_NUMBER (R_ARM_ALU_PCREL23_15,  	 34)   /* obsolete */
	  RELOC_NUMBER (R_ARM_LDR_SBREL_11_0,  	 35)   /* deprecated, should have _NC suffix */
	  RELOC_NUMBER (R_ARM_ALU_SBREL_19_12, 	 36)   /* deprecated, should have _NC suffix */
	  RELOC_NUMBER (R_ARM_ALU_SBREL_27_20, 	 37)   /* deprecated, should have _CK suffix */
	/****32~95 arm reserved********************/
	/* 96~111 reserved to g++ */
	/* 112 - 127 private range  */
	/* 128 ~248 reserved to arm   */
	/* 249~255  reserved to dynamic relocation .so  */
	/* Unofficial names for some of the relocs.  */
	  FAKE_RELOC (R_ARM_THM_PC22,           R_ARM_THM_CALL)
	  /* Relocs with both a different name, and (apparently) different meaning in GNU usage.  */
	  FAKE_RELOC (R_ARM_AMP_VCALL9,         R_ARM_BREL_ADJ)   /* Thumb-something.  Not used.  */
	  __R_ARM_COMPLETE__
};

typedef unsigned char BOOL ;
/* Extracted from reloc.c.  */
typedef enum arm_reloc_status
{
	  arm_reloc_ok,
	  arm_reloc_overflow,
	  arm_reloc_outofrange,
	  arm_reloc_continue,
	  arm_reloc_notsupported,
	  arm_reloc_other,
	  arm_reloc_undefined,
	  arm_reloc_dangerous
 }arm_reloc_status_type;

enum complain_overflow
{
	  complain_overflow_dont,
	  complain_overflow_bitfield,
	  complain_overflow_signed,
	  complain_overflow_unsigned
};

struct reloc_howto_struct
{
	  unsigned int type;
	  unsigned int rightshift;
	  int size;
	  unsigned int bitsize;
	  BOOL pc_relative;
	  unsigned int bitpos;
	  enum complain_overflow complain_on_overflow;
	  arm_reloc_status_type (*special_function)(void);
	  char *name;
	  BOOL  partial_inplace;
	  Elf32_Word src_mask;
	  Elf32_Word dst_mask;
	  BOOL  pcrel_offset;
};

typedef const struct reloc_howto_struct reloc_howto_type;

#define HOWTO(C, R, S, B, P, BI, O, SF, NAME, INPLACE, MASKSRC, MASKDST, PC) \
  { (unsigned) C, R, S, B, P, BI, O, SF, NAME, INPLACE, MASKSRC, MASKDST, PC }

 #define NEWHOWTO(FUNCTION, NAME, SIZE, REL, IN) \
  HOWTO (0, 0, SIZE, 0, REL, 0, complain_overflow_dont, FUNCTION, \
         NAME, FALSE, 0, 0, IN)

#define EMPTY_HOWTO(C) \
  HOWTO ((C), 0, 0, 0, FALSE, 0, complain_overflow_dont, NULL, \
         NULL, FALSE, 0, 0, FALSE)

#define ELF_ST_BIND(val)		(((unsigned int)(val)) >> 4)
#define ELF_ST_TYPE(val)		((val) & 0xF)
#define ELF_ST_INFO(bind,type)		(((bind) << 4) + ((type) & 0xF))


#define STB_LOCAL	0		/* Symbol not visible outside obj */
#define STB_GLOBAL	1		/* Symbol visible outside obj */
#define STB_WEAK	2		/* Like globals, lower precedence */
#define STB_LOOS	10		/* OS-specific semantics */
#define STB_HIOS	12		/* OS-specific semantics */
#define STB_LOPROC	13		/* Application-specific semantics */
#define STB_HIPROC	15		/* Application-specific semantics */

#define STT_NOTYPE	0		/* Symbol type is unspecified */
#define STT_OBJECT	1		/* Symbol is a data object */
#define STT_FUNC	2		/* Symbol is a code object */
#define STT_SECTION	3		/* Symbol associated with a section */
#define STT_FILE		4		/* Symbol gives a file name */
#define STT_COMMON	5		/* An uninitialised common block */
#define STT_TLS		6		/* Thread local data object */
#define STT_LOOS	10		/* OS-specific semantics */
#define STT_HIOS	12		/* OS-specific semantics */
#define STT_LOPROC	13		/* Application-specific semantics */
#define STT_HIPROC	15		/* Application-specific semantics */


#define STT_ARM_TFUNC                                  STT_LOPROC   /* A Thumb function.  */
#define STT_ARM_16BIT      STT_HIPROC     /* A Thumb label.  */
#define linker_abs(x)		(((x) >= 0) ? (x) : -(x))


typedef unsigned long bmd_vma;
typedef long bmd_signed_vma;

//thumb -> arm instruction
typedef struct 
{
#if DLL_THUMB_SUPPORT
	short int  tbx_inst; //U16 .must be 2bytes align
	short int  tnop_inst; //U16
#endif
	int ldr_inst;   //must be 4 bytes align
	int bx_inst;
	int dcd_inst;
}thumb_arm_veneer;

typedef struct
{
	thumb_arm_veneer veneer_object;
	char *sym_name;
}thumb_arm_veneer_stub;

#endif


#ifndef __PLT_RES_H__
#define __PLT_RES_H__

typedef unsigned char SYM_TYPE;

#define MAX_SYM_NAME_LEN  50
#define ARM_INST 0
#define THUMB_INST 1
#define NO_INST 2
#define UNDEF_INST 3

struct Sym_Info
{
	char* sym_name;
	void* sym_addr;
	SYM_TYPE sym_type;
};

void plt_get_host_symbol_info(char *symbol_name, struct Sym_Info*sym_info);
#endif

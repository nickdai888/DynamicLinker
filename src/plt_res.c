#include "..\inc\plt_res.h"
#include "..\inc\plt_lyr.h"


 void * __rt_memcpy( void *, const void *, size_t );
 void   __rt_memset(void *,int,size_t);
 void mmi_audply_entry_main();
 
// void * __16__rt_memcpy( void *, const void *, size_t );
 
#if _ADS_PLATFORM_

	/**********************************************
	* sym_type  'A'  'T'  'D'
	***********************************************/
	struct Sym_Info host_sym_info[] =
	{
		{"_printf",(void*)_printf,ARM_INST},
		{"_sprintf",(void*)_sprintf,ARM_INST},
		{"__rt_memcpy",(void*)__rt_memcpy,ARM_INST}
	};
#elif _WIN_PLATFORM_
	struct Sym_Info host_sym_info[] =
	{
			{"printf",(void*)printf,ARM_INST},
	};
	
#elif _MTK_HARDWARE_
	/**********************************************
	* sym_type  'A'  'T'  'D'
	***********************************************/
	struct Sym_Info host_sym_info[] =
	{
		{"DisplayPopup",(void*)DisplayPopup,THUMB_INST},
		{"mmi_audply_entry_main", (void*)mmi_audply_entry_main,THUMB_INST},
		{"__rt_memcpy",(void*)__rt_memcpy,THUMB_INST},
		{"__rt_memset",(void*)__rt_memset,THUMB_INST}
	};
#else
	struct Sym_Info host_sym_info[] =
	{
	}
#endif

//get function number of the host api function
int 
plt_get_host_function_number(void )
{
	int count = 0;
	int index = 0;
	for(index = 0; index < sizeof(host_sym_info)/sizeof(struct Sym_Info); index++)
	{
		if(host_sym_info[index].sym_type != NO_INST)
		count++;		
	}
	return count;
}


void plt_get_host_symbol_info(char *symbol_name, struct Sym_Info*sym_info)
{	
	int index = 0;
	dll_memset(sym_info, 0, sizeof(struct Sym_Info));//clear result firstly
	for(index = 0; index < sizeof(host_sym_info)/sizeof(struct Sym_Info); index++)
		{
			if(0 == dll_strcmp(host_sym_info[index].sym_name, symbol_name))
			{
				sym_info->sym_addr = host_sym_info[index].sym_addr;
				sym_info->sym_type = host_sym_info[index].sym_type;
				sym_info->sym_name = host_sym_info[index].sym_name; //the address is ro-address, assign it directly
				break;
			}
		}
	return;
}






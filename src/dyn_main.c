#include "..\inc\dyn_prot.h"
#include "..\inc\interface.h"
#include "stdio.h"

typedef int(*func_type)(void);

#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_
 int  dll_generate_pltres_info(WCHAR *dll_file_path,WCHAR *output_file_path);
#if 0
int main(int a)//test
{
	dll_generate_pltres_info(L"E:\\nick.obj",L"E:\\nick.log");
}
#endif
#define WIN_MAX_FILE_NAME 512
WCHAR dll_output_file_path[WIN_MAX_FILE_NAME];
 int  dll_generate_pltres_info(WCHAR *dll_file_path,WCHAR *output_file_path)
#else
int main(int a)
#endif
{
	func_type  call_thumb_func = NULL;
	 DLL_INSTANCE_HANDLER instance = NULL;
	#if _DLL_GENERATE_SYMBOL_INFO_FILE_&_WIN_PLATFORM_
	if(NULL == dll_file_path)
	{
		return 0;
	}
	   dll_wcscpy(dll_output_file_path, output_file_path);
	  instance =  LoadLibrary(dll_file_path);
	 
	#else
	 instance =  LoadLibrary(L"D:\\Project\\Dynamic\\pro\\DYN\\mini.obj");
	#endif
	call_thumb_func =(func_type)GetProcAddress( instance, "entrance");
	(int)call_thumb_func |=1;
	if(NULL != call_thumb_func)
	{
#if _MTK_HARDWARE_|_ADS_PLATFORM_
		(*call_thumb_func)();
#endif
	}
	FreeLibrary(instance);
	return 0;
}


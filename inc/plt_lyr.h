/********************************************************************************
* platform porting layer
* porting to different platform
*********************************************************************************/
#ifndef __PLT_LYR_H__
#define __PLT_LYR_H__
/***************platform definition***************/
#define _CUR_PLATFORM_   2  //PLATFORM TO CHOOSE
#define _MTK_PLATFROM_ (_CUR_PLATFORM_ == 1)  // MTK MODIS 
#define _ADS_PLATFORM_ (_CUR_PLATFORM_ == 2)  // ADS1.2 AXD
#define _WIN_PLATFORM_ (_CUR_PLATFORM_ == 3)  // WINDOWS  VC6.0
#define _MTK_HARDWARE_ (_CUR_PLATFORM_ == 4)  // MTK  HARDWARE

#ifndef __OFF__
#define __OFF__  0
#endif
#ifndef __ON__
#define __ON__   1
#endif

#define _DLL_DEBUG_  __ON__
#define _DLL_GENERATE_SYMBOL_INFO_FILE_ __OFF__
#define _DLL_MAX_OBJECT_SYMBOL_COUNT_ 5000


#define DLL_THUMB_SUPPORT  __ON__

/****************basic type definition************/
typedef unsigned int UINT;
typedef unsigned short WCHAR;
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;


/************************TRACE********************/
#if _DLL_DEBUG_

	#if _MTK_HARDWARE_
		#define DLL_TRACE  Trace
	#else
		#define DLL_TRACE  printf
	#endif

#else
		#define DLL_TRACE(...)  {}
#endif

/**********************File System*****************/
#if (_ADS_PLATFORM_)||(_WIN_PLATFORM_)
	#include "stdio.h"
	#include "stdlib.h"
	#include "string.h"
	typedef FILE* FS_HANDLE;
#elif(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
    #include "MMIDataType.h"
    #include "fs_type.h"
    #include "fs_func.h"
#endif

#if _ADS_PLATFORM_
	#include "alloca.h"
#elif _WIN_PLATFORM_
	#include "malloc.h"
#endif

typedef enum 
{
	DLL_FS_READ_ONLY,
	DLL_FS_READ_WRITE,
	DLL_FS_CREATE,
	DLL_FS_CREATE_ALWAYS
}DLL_FSOPEN_FLAG;

typedef enum 
{
   DLL_FS_FILE_BEGIN,
   DLL_FS_FILE_CURRENT,
   DLL_FS_FILE_END
}DLL_FSEEK_POS_FLAG;

FS_HANDLE dll_fopen(const WCHAR * FileName,DLL_FSOPEN_FLAG Flag);
int  dll_fclose(FS_HANDLE FileHandle);
int  dll_fseek (FS_HANDLE FileHandle, int Offset, DLL_FSEEK_POS_FLAG Whence);
UINT dll_fread (FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Read);
UINT dll_fwrite (FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Written);



/*********************Memory**********************/
void   dll_free(void *ptr);
void * dll_malloc(unsigned int size,const char *file, int line);
#define GLOBAL_MALLOC(size) dll_malloc((size),__FILE__,__LINE__)
#define GLOBAL_FREE(ptr) dll_free(ptr)

void *dll_memset( void *dest, int c, unsigned int count );
void *dll_memcpy( void *dest, const void *src, unsigned int  count );

/*********************String*********************/
char *dll_strcpy( char *strDestination, const char *strSource );
WCHAR *dll_wcscpy( WCHAR *strDestination, const WCHAR *strSource );
char *dll_strncpy( char *strDest, const char *strSource, int count );
WCHAR *dll_wcsncpy( WCHAR *strDest, const WCHAR *strSource, int count );


char *dll_strcat( char *strDestination, const char *strSource );
WCHAR *dll_wcscat( WCHAR *strDestination, const WCHAR *strSource );

int dll_strcmp( const char *string1, const char *string2 );
int dll_wcscmp( const WCHAR *string1, const WCHAR *string2 );

char *dll_strstr( const char *string, const char *strCharSet );
WCHAR *dll_wcsstr( const WCHAR *string, const WCHAR *strCharSet );

int dll_strlen( const char *string );
int dll_wcslen( const WCHAR *string );

#endif


#include "..\inc\plt_lyr.h"
static int malloc_count = 0; 
/*The following code is for MTK platform special*/
#if _MTK_HARDWARE_
#define DLL_HEAP_SIZE (200*1024)
static kal_uint8 dll_heap[DLL_HEAP_SIZE];
static KAL_ADM_ID dll_dm_id = 0;

BOOL dll_create_mempool(void)
{
	if(dll_dm_id == NULL)
	{
		dll_dm_id = kal_adm_create(dll_heap, DLL_HEAP_SIZE, NULL, KAL_FALSE);
		if(dll_dm_id == NULL)
		{
			DLL_TRACE("create memory pool failed\n");
			return FALSE;
		}
	}
	return TRUE;
}

void dll_delete_mempool()
{
	 kal_adm_delete(dll_dm_id);
	 dll_dm_id = NULL;
}
#endif


void* dll_malloc(unsigned int size,const char *file, int line)
{
	void *addr = NULL;
	#if _MTK_HARDWARE_
		addr = (void*)kal_adm_alloc(dll_dm_id, size);
	#else
		addr = (void*)malloc(size);
	#endif
	if(NULL == addr)
	{
		DLL_TRACE("!!----DLL Malloc Failed at File:%s,Line:%d,Size:%d---!!\n", file, line, size);
	}
	else
	{
		malloc_count++;
	}
	return (void*)addr;
}

void dll_free(void * addr)
{
	if(NULL != addr)
	{
		#if _MTK_HARDWARE_
			kal_adm_free(dll_dm_id, addr);
		#else
			free(addr);
		#endif
		malloc_count--;
	}
	
}

 void *dll_memset( void *dest, int c, unsigned int count )
{
	return memset(dest, c, count);	
}

 void *dll_memcpy( void *dest, const void *src, unsigned int  count )
{
	return memcpy(dest , src, count);
}


unsigned short elf_ucs2_str_to_asc_str(char *pOutBuffer, char *pInBuffer)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    unsigned short count = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (!((*pInBuffer == 0) && (*(pInBuffer + 1) == 0)))
    {
        *pOutBuffer = *(pInBuffer);
        pInBuffer += 2;
        pOutBuffer++;
        count++;
    }

    *pOutBuffer = 0;
    return count;
}


/************FILE SYSTEM API< PORTING TO DIFFERENT PLATFORM>*********************/
FS_HANDLE dll_fopen(const WCHAR * FileName,DLL_FSOPEN_FLAG Flag)
{
	FS_HANDLE fhandler = NULL;
	#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
	  if(Flag == DLL_FS_READ_ONLY)
	  	{
	  		fhandler = FS_Open(FileName, FS_READ_ONLY);
	  	}
	  else if(Flag == DLL_FS_READ_WRITE)
	  	{
	  		fhandler = FS_Open(FileName, FS_READ_WRITE);
	  	}
	  else if(Flag == DLL_FS_CREATE)
	  	{
	  		fhandler = FS_Open(FileName, FS_CREATE);
	  	}
	  else if(Flag == DLL_FS_CREATE_ALWAYS)
	  	{
	  		fhandler = FS_Open(FileName, FS_CREATE_ALWAYS);
	  	}
	  else
	  	{
	  		fhandler = NULL;
	  	}
	#elif(_ADS_PLATFORM_)||(_WIN_PLATFORM_)
	  char dllFilePath[128];
	  elf_ucs2_str_to_asc_str(dllFilePath,(char*)FileName);
	  if(Flag == DLL_FS_READ_ONLY)
	  	{
	  		fhandler = fopen(dllFilePath, "rb");
	  	}
	  else if(Flag == DLL_FS_READ_WRITE)
	  	{
	  		fhandler = fopen(dllFilePath, "rb+");
	  	}
	  else if(Flag == DLL_FS_CREATE)
	  	{
	  		fhandler = fopen(dllFilePath, "ab+");
	  	}
	  else if(Flag == DLL_FS_CREATE_ALWAYS)
	  	{
	  		fhandler = fopen(dllFilePath, "wb+");
	  	}
	  else
	  	{
	  		fhandler = NULL;
	  	}
	#endif
	return fhandler;
}

int dll_fclose(FS_HANDLE FileHandle)
{
	#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
		 return FS_Close(FileHandle);
	#elif(_ADS_PLATFORM_)||(_WIN_PLATFORM_)
		 return fclose(FileHandle);
	#endif
}

int dll_fseek (FS_HANDLE FileHandle, int Offset, DLL_FSEEK_POS_FLAG Whence)
{
	int seek_reslut = 0;
	#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
	 if( Whence == DLL_FS_FILE_BEGIN)
	 	{
	 		seek_reslut = FS_Seek( FileHandle,Offset,FS_FILE_BEGIN );
	 	}
	 else if(Whence == DLL_FS_FILE_CURRENT)
	 	{
	 		seek_reslut = FS_Seek( FileHandle,Offset,FS_FILE_CURRENT );
	 	}
	 else
		{
			seek_reslut = FS_Seek( FileHandle,Offset,FS_FILE_END );
		}
		
	#elif(_ADS_PLATFORM_)||(_WIN_PLATFORM_)
	 if( Whence == DLL_FS_FILE_BEGIN)
	 	{
	 		seek_reslut = fseek( FileHandle,Offset, SEEK_SET );
	 	}
	 else if(Whence == DLL_FS_FILE_CURRENT)
	 	{
	 		seek_reslut = fseek( FileHandle, Offset, SEEK_CUR );
	 	}
	 else
		{
			seek_reslut = fseek( FileHandle, Offset, SEEK_END );
		}
	#endif
	return seek_reslut;

}

UINT dll_fread (FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Read)
{
	UINT  rd_bytes = 0;
	#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
		FS_Read( FileHandle,(void*)DataPtr,Length,&rd_bytes);
	#elif(_ADS_PLATFORM_)||(_WIN_PLATFORM_)
		rd_bytes = fread((void*)DataPtr, 1, Length, FileHandle );
	#endif
	*Read = rd_bytes;
	return rd_bytes;

}
UINT dll_fwrite (FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Written)
{
	UINT wt_bytes = 0;
	#if(_MTK_PLATFROM_)||(_MTK_HARDWARE_)
		FS_Write(FileHandle, DataPtr, Length, (UINT*)&wt_bytes));
	#elif(_ADS_PLATFORM_)||(_WIN_PLATFORM_)
		wt_bytes =  fwrite( DataPtr, 1 , Length, FileHandle );
	#endif
	*Written = wt_bytes;
	return wt_bytes;
}


/**************************String API*******************************/
  char *dll_strcpy( char *strDestination, const char *strSource )
{
	return strcpy( strDestination, strSource );
}
  char *dll_strncpy( char *strDest, const char *strSource, int count )
{
	return strncpy( strDest, strSource,  count );
}

  char *dll_strcat( char *strDestination, const char *strSource )
{
	return strcat( strDestination, strSource );
}

  int dll_strcmp( const char *string1, const char *string2 )
{
	return strcmp( string1, string2 );
}

  char *dll_strstr( const char *string, const char *strCharSet )
{
	return strstr( string, strCharSet );
}
  int dll_strlen( const char *string )
{
	return strlen( string );
}

#if _ADS_PLATFORM_|_WIN_PLATFORM_

 /*****************************************************************************
  * FUNCTION
  *  app_ucs2_wcscpy
  * DESCRIPTION
  *  Copies the UCS2 encoded source string(wide-character) into the destination 
  *  string; Assumes enough space in the destination string.
  * PARAMETERS
  *  str_dst   [OUT]  UCS2 encoded destination string(wide-character) over which 
  * 				  the source string is to be copied.
  *  str_src   [IN]   UCS2 encoded source string(wide-character) to be copied 
  * 				  over the destination string.
  * RETURNS
  *  A pointer to the destination string.
  *****************************************************************************/
 WCHAR *app_ucs2_wcscpy(WCHAR *str_dst, const WCHAR *str_src)
 {
	 /*----------------------------------------------------------------*/
	 /* Local Variables 											   */
	 /*----------------------------------------------------------------*/
	 WCHAR *str_tmp = str_dst;
 
	 /*----------------------------------------------------------------*/
	 /* Code Body													   */
	 /*----------------------------------------------------------------*/
	 *str_tmp = *str_src;
	 
	 while(*str_src)
	 {
		 *(++str_tmp) = *(++str_src); /* Copy str_src over str_dst */
	 }
	 return str_dst;
 }



 
/*****************************************************************************
 * FUNCTION
 *  app_ucs2_wcsncpy
 * DESCRIPTION
 *  Copies count characters from the source string to the destination string.  
 *  Note:
 *  Unlike ANSI C standard library function wcsncpy. If count is less than the 
 *  length of source, NULL wide-characters also is put onto the end of the 
 *  copied string. But if count is greater than the length of sources, str_dst 
 *  is not padded with null characters to length count (wide-characters).
 * PARAMETERS
 *  str_dst   [OUT]  UCS2 encoded destination string(wide-character) over which 
 *                   the source string is to be copied.
 *  str_src   [IN]   UCS2 encoded source string(wide-character) to be copied 
 *                   over the destination string.
 *  count     [IN]   max number of characters to copy.
 * RETURNS
 *  A pointer to the destination string.
 *****************************************************************************/
WCHAR *app_ucs2_wcsncpy(WCHAR *str_dst, const WCHAR *str_src, U32 count)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    WCHAR *str_tmp = str_dst;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (count && *str_src)
    {    
        *str_tmp = *str_src; /* copy string */
        ++str_tmp, ++str_src;
        --count;
    }    
    
    *str_tmp = L'\0';   
    
    return str_dst;
}


/*****************************************************************************
 * FUNCTION
 *  app_ucs2_wcsstr
 * DESCRIPTION
 *  Find a substring.
 * PARAMETERS
 *  string        [IN]  UCS2 encoded string(wide-character) to search.       
 *  str_char_set  [IN]  UCS2 encoded string(wide-character) to search for.      
 * RETURNS
 *  Returns a pointer to the first occurrence of str_char_set in string, or 
 *  NULL if str_char_set does not appear in string. If str_char_set points to 
 *  a string of zero length, the function returns string. 
 *****************************************************************************/
WCHAR *app_ucs2_wcsstr(const WCHAR *string, const WCHAR *str_char_set)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    WCHAR *str_tmp = (WCHAR *) string;
    WCHAR *cursor1, *cursor2;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (*str_tmp)
    {
        cursor1 = str_tmp;
        cursor2 = (WCHAR *) str_char_set;

        while ((*cursor1)&&(*cursor2)&&!(*cursor1 - *cursor2))
        {
            cursor1++, cursor2++;
        }

        if (!*cursor2)
        {
            return str_tmp;
        }

        ++str_tmp;
    }

    return NULL;
}


/*****************************************************************************
 * FUNCTION
 *  app_ucs2_wcslen
 * DESCRIPTION
 *  Gets the number of characters of the given UCS2 encoded string(wide-character), 
 *  not including the final null wide-characters.
 * PARAMETERS          
 *  string    [IN]  UCS2 encoded string(wide-character) which length is to
 *                  be computed.      
 * RETURNS
 *  The number of characters of a wide-character string.
 *****************************************************************************/
int app_ucs2_wcslen(const WCHAR *string)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    const WCHAR *str_tmp = string;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while(*str_tmp)
    {
        ++str_tmp;
    }
    
    return (int) (str_tmp - string);
}


/*****************************************************************************
 * FUNCTION
 *  app_ucs2_wcscmp
 * DESCRIPTION
 *  Compares two UCS2 encoded strings(wide-character) and returns an integer to 
 *  indicate whether the destination string is less than the source string, 
 *  the two are equal, or whether the destination string is greater than the 
 *  source string.
 * PARAMETERS          
 *  str_src   [IN]  UCS2 encoded destination string(wide-character) for 
 *                  left-hand side of comparison.
 *  str_dst   [IN]  UCS2 encoded source string(wide-character) for right-hand 
 *                  side of comparison.       
 * RETURNS
 *  returns <0 if str_src <  str_dst
 *  returns  0 if str_src == str_dst
 *  returns >0 if str_src >  str_dst
 *****************************************************************************/
int app_ucs2_wcscmp(const WCHAR *str_src, const WCHAR *str_dst)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while((*str_src == *str_dst) && *str_src)
    {
        ++str_src, ++str_dst;        
    }      

    return (int)(*str_src - *str_dst);
}


/*****************************************************************************
 * FUNCTION
 *  app_ucs2_wcscat
 * DESCRIPTION
 *  Concatenates the source string onto the end of the destination string. 
 *  Assumes enough space in the destination string.
 * PARAMETERS
 *  str_dst   [OUT]  UCS2 encoded destination string(wide-character) over which 
 *                   "str_src" is to be copied.      
 *  str_src   [IN]   UCS2 encoded source string(wide-character) to be copied 
 *                   over "str_dst".      
 * RETURNS
 *  A pointer to the destination string.
 *****************************************************************************/
WCHAR *app_ucs2_wcscat(WCHAR *str_dst, const WCHAR *str_src)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    WCHAR *str_tmp = str_dst;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/    
	while(*str_tmp)
    {
        ++str_tmp;            /* find end of str_dst */
    }
    
    while(*str_src)
    {
        *str_tmp= *str_src;   /* Copy str_src to end of str_dst */
        ++str_tmp, ++str_src;
    }

    *str_tmp = L'\0';

    return  str_dst;          /* return str_dst */
}

#endif

  WCHAR *dll_wcscpy( WCHAR *strDestination, const WCHAR *strSource )
{
	 return (WCHAR *)app_ucs2_wcscpy(strDestination, strSource);
}

  WCHAR *dll_wcsncpy( WCHAR *strDest, const WCHAR *strSource, int count )
{
	return app_ucs2_wcsncpy(strDest, strSource, count);
}

  WCHAR *dll_wcsstr( const WCHAR *string, const WCHAR *strCharSet )
{
	return app_ucs2_wcsstr(string, strCharSet);
}

  WCHAR *dll_wcscat( WCHAR *strDestination, const WCHAR *strSource )
{
	return app_ucs2_wcscat(strDestination, strSource);
}

  int dll_wcscmp( const WCHAR *string1, const WCHAR *string2 )
{
	return app_ucs2_wcscmp(string1, string2);
}

  int dll_wcslen( const WCHAR *string )
{
    return app_ucs2_wcslen(string);
}



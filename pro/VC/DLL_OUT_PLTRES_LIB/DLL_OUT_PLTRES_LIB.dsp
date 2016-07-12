# Microsoft Developer Studio Project File - Name="DLL_OUT_PLTRES_LIB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DLL_OUT_PLTRES_LIB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DLL_OUT_PLTRES_LIB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DLL_OUT_PLTRES_LIB.mak" CFG="DLL_OUT_PLTRES_LIB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DLL_OUT_PLTRES_LIB - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DLL_OUT_PLTRES_LIB - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DLL_OUT_PLTRES_LIB - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "DLL_OUT_PLTRES_LIB - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "DLL_OUT_PLTRES_LIB - Win32 Release"
# Name "DLL_OUT_PLTRES_LIB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\arm_elf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dyn_main.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\interface.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\linker.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\loader.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\plt_lyr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\plt_res.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\inc\arm_elf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\dyn_prot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\linker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\loader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\plt_lyr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\inc\plt_res.h
# End Source File
# End Group
# End Target
# End Project

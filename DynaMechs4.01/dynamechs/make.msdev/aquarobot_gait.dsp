# Microsoft Developer Studio Project File - Name="aquarobot_gait" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=aquarobot_gait - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aquarobot_gait.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aquarobot_gait.mak" CFG="aquarobot_gait - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aquarobot_gait - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "aquarobot_gait - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aquarobot_gait - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib/platform.msvc60.i686"
# PROP Intermediate_Dir "../obj/platform.msvc60.i686"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AQUAROBOT_GAIT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /Op /I "..\aquarobot" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "aquarobot_DLL_FILE" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /incremental:yes /machine:I386 /libpath:"../lib/platform.msvc60.i686"

!ELSEIF  "$(CFG)" == "aquarobot_gait - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib/platform.msvc60.i686.dbg"
# PROP Intermediate_Dir "../obj/platform.msvc60.i686.dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AQUAROBOT_GAIT_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /GR /GX /ZI /Od /I "..\aquarobot" /D "aquarobot_DLL_FILE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"../lib/platform.msvc60.i686.dbg"

!ENDIF 

# Begin Target

# Name "aquarobot_gait - Win32 Release"
# Name "aquarobot_gait - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\aquarobot\Body.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\EulerAng.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\GaitAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Leg.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\LegLink.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\MatrixMy.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Posture.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Robot.cpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Vector.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\aquarobot\Aquarobo.h
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Body.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\EulerAng.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Gait.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\GaitAlgorithm.h
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Leg.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\LegLink.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\MatrixMy.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Posture.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Robot.hpp
# End Source File
# Begin Source File

SOURCE=..\aquarobot\Vector.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

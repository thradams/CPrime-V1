
#define VISUAL_STUDIO_2017
//#define MINGW


#ifdef VISUAL_STUDIO_2017

#define _M_IX86 400
#define WIN32
#define __STDC__ 0
#define _WIN32
#define _RELEASE
#define _CONSOLE
#define _UNICODE
#define UNICODE

#define _M_IX86
#define __stdcall
#define __fastcall
#define __pragma(x)  
#define __inline  
#define  __cdecl  
#define __declspec(x)          
#define __int64 long long
//#define _MSC_VER  1300
#define __ptr64

#pragma dir "c:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared"
#pragma dir "c:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\um"
#pragma dir "c:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt" 
#pragma dir "c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\include"

#elif MINGW

#define __cdecl
#define __inline__
#define __declspec(x)
#define __restrict__

#pragma dir "C:\MinGW\include"
#pragma dir "C:\MinGW\lib\gcc\mingw32\6.3.0\include"

#endif

#undef VISUAL_STUDIO_2017





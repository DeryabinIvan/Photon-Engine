// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined(PHOTONENGINE_EXPORTS)
	#define PHOTONENGINE_API __declspec(dllexport)
#else
	#define PHOTONENGINE_API __declspec(dllimport)
#endif

#include "targetver.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

typedef unsigned int uint;

#pragma warning( disable:4251 )
#pragma warning( disable:4275 )
#pragma warning( disable:4091 )

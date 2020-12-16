#pragma once

#ifndef __DLL_EXPORT
#ifndef __DLL_IMPORT
#ifdef WIN32
#define __DLL_EXPORT __declspec(dllexport)
#define __DLL_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define __DLL_EXPORT __attribute__((visibility("default")))
#define __DLL_IMPORT
#else
#define __DLL_EXPORT
#define __DLL_IMPORT
#endif
#endif
#endif


#ifdef MAZE_EXPORTS
#define MAZE_API __DLL_EXPORT
#else
#define MAZE_API __DLL_IMPORT
#endif

#pragma once

#ifdef REAL_PLATFORM_WINDOWS
	#ifdef REAL_BUILD_DLL
		#define REAL_EXPORT __declspec(dllexport)
	#else
		#define REAL_EXPORT __declspec(dllimport)
	#endif
#else
	#error Currently only supports windows
#endif

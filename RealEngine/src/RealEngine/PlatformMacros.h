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

#ifdef REAL_ASSERTS
	#define REAL_CORE_ASSERT(x,...) { if(!(x)){ RL_CORE_ERROR("Assertion Failed {}",__VA_ARGS__); __debugbreak(); } }
	#define REAL_ASSERT(x,...)      { if(!(x)){ RL_ERROR("Assertion Failed {}",__VA_ARGS__); __debugbreak(); } }
#else
#define REAL_CORE_ASSERT(x,...)
#define REAL_ASSERT(x,...)     
#endif
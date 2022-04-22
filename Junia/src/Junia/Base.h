#pragma once

#ifdef JE_PLATFORM_WINDOWS
	#ifdef JE_BUILD_DLL
		#define JUNIA_API __declspec(dllexport)
	#else
		#define JUNIA_API __declspec(dllimport)
	#endif
#else
	#error Junia is only supported on Windows!
#endif

#define BITFIELD(x) (1 << (x))

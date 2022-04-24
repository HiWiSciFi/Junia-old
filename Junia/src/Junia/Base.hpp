#pragma once

#ifdef JE_TARGETPLATFORM_WINDOWS
	#ifdef JE_EXPORT
		#define JE_API_IO __declspec(dllexport)
	#else
		#define JE_API_IO __declspec(dllimport)
	#endif
#else
	#error Junia is only supported on Windows!
#endif

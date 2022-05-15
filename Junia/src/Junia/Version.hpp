#pragma once
#include "Base.hpp"

namespace Junia
{
	#define JE_VERSION_MAJOR (unsigned int)1
	#define JE_VERSION_MINOR (unsigned int)0
	#define JE_VERSION_PATCH (unsigned int)0

	class JE_API_IO Version
	{
	public:
		static unsigned int GetMajor();
		static unsigned int GetMinor();
		static unsigned int GetPatch();

		static const char* GetCompilationDate();
		static const char* GetCompilationTime();
	};
}

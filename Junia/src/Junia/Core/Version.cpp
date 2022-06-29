#include "Version.hpp"

namespace Junia
{
	unsigned int Version::GetMajor()
	{
		return JE_VERSION_MAJOR;
	}

	unsigned int Version::GetMinor()
	{
		return JE_VERSION_MINOR;
	}

	unsigned int Version::GetPatch()
	{
		return JE_VERSION_PATCH;
	}

	const char* Version::GetCompilationDate()
	{
		return __DATE__;
	}

	const char* Version::GetCompilationTime()
	{
		return __TIME__;
	}
}

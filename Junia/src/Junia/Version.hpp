#pragma once
#include <string>
#include <sstream>

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

	inline std::string GetCompileVersion()
	{
		std::stringstream ss;
		ss << Version::GetMajor() << "." << Version::GetMinor() << "." << Version::GetPatch();
		return ss.str();
	}

	inline std::string GetHeaderVersion()
	{
		std::stringstream ss;
		ss << JE_VERSION_MAJOR << "." << JE_VERSION_MINOR << "." << JE_VERSION_PATCH;
		return ss.str();
	}

	inline bool HeaderCompileVersionMatch()
	{
		return Version::GetMajor() == JE_VERSION_MAJOR && Version::GetMinor() == JE_VERSION_MINOR && Version::GetPatch() == JE_VERSION_PATCH;
	}
}

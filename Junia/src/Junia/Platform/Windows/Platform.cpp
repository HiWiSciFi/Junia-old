#ifdef JE_TARGETPLATFORM_WINDOWS

#include "../Platform.hpp"

#include <Windows.h>
#include <Junia/Log.hpp>
#include <fstream>

namespace Junia
{
	float Platform::GetTime()
	{
		unsigned long timems = timeGetTime();
		return timems / 1000.0f;
	}

	std::string Platform::LoadFileAsString(const std::string& path)
	{
		HANDLE hfile;
		std::wstring stemp = std::wstring(path.begin(), path.end());
		LPCWSTR winpath = stemp.c_str();
		hfile = CreateFile(winpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL /*FILE_ATTRIBUTE_NORMAL*/, NULL);

		if (hfile == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
				JELOG_BASE_ERROR("File at \"%s\" does not exist!", path.c_str());
			return "";
		}

		// TODO: continue
		return "";
	}

	std::string Platform::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		} else JELOG_BASE_ERROR("File at " JELOG_CSTR " could not be loaded!", filepath.c_str());
		return result;
	}
}

#endif

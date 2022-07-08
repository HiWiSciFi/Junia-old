#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32

#include "../Platform.hpp"
#include <Junia/Platform/Windows/Win32.hpp>
#include <Junia/Core/Log.hpp>
#include <fstream>

namespace Junia
{
	float Platform::GetTime()
	{
		const auto timems = WinTime_GetTime();
		return static_cast<float>(timems) / 1000.0f;
	}

	std::string Platform::LoadFileAsString(const std::string& path)
	{
		//const auto stemp = std::wstring(path.begin(), path.end());
		//const LPCWSTR winpath = stemp.c_str();
		//const HANDLE hfile = CreateFile(winpath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
		//                                NULL /*FILE_ATTRIBUTE_NORMAL*/, nullptr);

		//if (hfile == INVALID_HANDLE_VALUE)
		//{
		//	JELOG_BASE_ASSERT(GetLastError() != ERROR_FILE_NOT_FOUND, "File at \"%s\" does not exist!", path.c_str());
		//	return "";
		//}

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

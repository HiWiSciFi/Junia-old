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
		FILE* file = fopen(filepath.c_str(), "rb");
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		fseek(file, 0, SEEK_SET);

		std::string fileBuffer(size, '\0');

		fread(&fileBuffer.at(0), size, 1, file);
		fclose(file);
		return fileBuffer;
	}
}

#endif

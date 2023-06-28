#include <Junia/Core/FileSystem.hpp>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE
#include <stdexcept>
#include <vector>
#include <cstdint>

namespace Junia {

// TODO: BOOL CloseHandle([in] HANDLE hObject) | Error handling
std::vector<uint8_t> ReadFileBinary(const std::string& path) {
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) throw std::runtime_error("failed to open file");

	LARGE_INTEGER fileSize;
	if (GetFileSizeEx(hFile, &fileSize) == FALSE) {
		if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
		throw std::runtime_error("failed to read file size");
	}

	std::vector<uint8_t> buffer(fileSize.QuadPart);
	if (ReadFile(hFile, buffer.data(), static_cast<DWORD>(buffer.size()), NULL, NULL) == FALSE) {
		if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
		throw std::runtime_error("failed to read file contents");
	}

	if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
	return buffer;
}

std::string ReadFileText(const std::string& path) {
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) throw std::runtime_error("failed to open file");

	LARGE_INTEGER fileSize;
	if (GetFileSizeEx(hFile, &fileSize) == FALSE) {
		if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
		throw std::runtime_error("failed to read file size");
	}

	std::string buffer(fileSize.QuadPart, '\0');
	if (ReadFile(hFile, buffer.data(), static_cast<DWORD>(buffer.size()), NULL, NULL) == FALSE) {
		if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
		throw std::runtime_error("failed to read file contents");
	}

	if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
	return buffer;
}

//class FileContentIterator {
//private:
//	HANDLE hFile = INVALID_HANDLE_VALUE;
//	std::vector<char> buffer{ };
//
//public:
//	FileContentIterator(const std::string& path) {
//		hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//		if (hFile == INVALID_HANDLE_VALUE) throw std::runtime_error("failed to open file");
//		buffer.resize(128);
//	}
//
//	void ReadLine(std::string& line) {
//		line.erase();
//		// TODO: implement
//	}
//
//	void Close() {
//		if (CloseHandle(hFile) == FALSE) throw std::runtime_error("failed to close file handle");
//		hFile = INVALID_HANDLE_VALUE;
//	}
//};

} // namespace Junia

#endif

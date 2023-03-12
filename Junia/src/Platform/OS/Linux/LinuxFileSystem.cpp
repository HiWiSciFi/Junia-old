#ifdef __linux__

#include <sys/stat.h>
#include <Junia/Core/FileSystem.hpp>
#include <stdexcept>
#include <fstream>

namespace Junia
{
	std::vector<uint8_t> ReadFileBinary(const std::string& path)
	{
		struct stat results;
		if (stat(path.c_str(), &results) != 0) throw std::runtime_error("failed to read file size");

		std::vector<uint8_t> buffer(results.st_size);
		std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
		if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size()))
			throw std::runtime_error("failed to read file contents");

		return buffer;
	}

	std::string ReadFileText(const std::string& path)
	{
		struct stat results;
		if (stat(path.c_str(), &results) != 0) throw std::runtime_error("failed to read file size");

		std::string buffer(results.st_size, '\0');
		std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
		if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size()))
			throw std::runtime_error("failed to read file contents");

		return std::string{ };
	}
}

#endif

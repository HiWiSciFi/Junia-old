#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Junia
{
	std::vector<uint8_t> ReadFileBinary(const std::string& path);
	std::string ReadFileText(const std::string& path);
}

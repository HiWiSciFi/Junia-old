#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Junia
{
	/**
	 * @brief Read a binary file
	 * @param path The path to the file
	 * @return a vector containing the bytes that have been read
	*/
	std::vector<uint8_t> ReadFileBinary(const std::string& path);

	/**
	 * @brief Read a text file
	 * @param path The path to the file
	 * @return A string containing the text that has been read
	*/
	std::string ReadFileText(const std::string& path);
}

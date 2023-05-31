#pragma once

#include <cstdint>
#include <string>

namespace Junia {

struct Version {
private:
	/**
	 * @brief Version number according to Vulkan 1.3 Spec 43.2.1 (excluding
	 *        variant)
	*/
	uint32_t version;

public:
	/**
	 * @brief Create a version struct
	 * @param major The major version number (7 bit)
	 * @param minor The minor version number (10 bit)
	 * @param patch The patch version number (12 bit)
	*/
	explicit Version(uint8_t major = 1, uint16_t minor = 0, uint16_t patch = 0);

	/**
	 * @brief Get the version number
	 * @return 32-Bit Version number according to Vulkan 1.3 Spec 43.2.1
	 *         (variant as 0)
	*/
	[[nodiscard]] uint32_t GetVersionNumber() const;

	/**
	 * @brief Get the major version number
	 * @return 8-Bit major version number
	*/
	[[nodiscard]] uint8_t GetMajor() const;

	/**
	 * @brief Get the minor version number
	 * @return 16-Bit minor version number
	*/
	[[nodiscard]] uint16_t GetMinor() const;

	/**
	 * @brief Get the patch version number
	 * @return 16-Bit patch version number
	*/
	[[nodiscard]] uint16_t GetPatch() const;

	/**
	 * @brief Alias for Version::GetPatch
	 * @return 16-Bit patch version number
	*/
	[[nodiscard]] uint16_t GetRevision() const;

	/**
	 * @brief Get the version as a string
	 * @return A string formatted as <major>.<minor>.<patch>
	*/
	[[nodiscard]] std::string GetVersionString() const;
};

} // namespace Junia

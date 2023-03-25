#pragma once

#include <cstdint>
#include <string>

namespace Junia
{
	struct Version
	{
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
		Version(uint8_t major = 1, uint16_t minor = 0, uint16_t patch = 0);

		/**
		 * @brief Get the version number
		 * @return 32-Bit Version number according to Vulkan 1.3 Spec 43.2.1
		 *         (variant as 0)
		*/
		inline uint32_t GetVersionNumber() const { return version; }

		/**
		 * @brief Get the major version number
		 * @return 8-Bit major version number
		*/
		inline uint8_t GetMajor() const { return static_cast<uint8_t>((version >> 22) & static_cast<uint32_t>(0x7FU)); }

		/**
		 * @brief Get the minor version number
		 * @return 16-Bit minor version number
		*/
		inline uint16_t GetMinor() const { return static_cast<uint16_t>((version >> 12) & static_cast<uint32_t>(0x3FFU)); }

		/**
		 * @brief Get the patch version number
		 * @return 16-Bit patch version number
		*/
		inline uint16_t GetPatch() const { return static_cast<uint16_t>(version & static_cast<uint32_t>(0xFFFU)); }

		/**
		 * @brief Alias for Version::GetPatch
		 * @return 16-Bit patch version number
		*/
		inline uint16_t GetRevision() const { return GetPatch(); }

		/**
		 * @brief Get the version as a string
		 * @return A string formatted as <major>.<minor>.<patch>
		*/
		std::string GetVersionString() const;
	};
}

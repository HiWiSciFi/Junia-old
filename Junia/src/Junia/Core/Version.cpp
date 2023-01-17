#include "Core.hpp"
#include <Junia/Core/Version.hpp>

#include <sstream>

namespace Junia
{
	Version::Version(uint8_t major, uint16_t minor, uint16_t patch)
	{
		version = static_cast<uint32_t>(0)
			| (static_cast<uint32_t>(major) << 22)
			| (static_cast<uint32_t>(minor) << 12)
			| (static_cast<uint32_t>(patch));
	}

	std::string Version::GetVersionString() const
	{
		std::stringstream ss;
		ss << static_cast<uint16_t>(GetMajor()) << '.' << GetMinor() << '.' << GetPatch();
		return ss.str();
	}
}

#include <Junia/Core/Version.hpp>

#include <sstream>

namespace Junia {

constexpr uint32_t MajorOffset = 22;
constexpr uint32_t MinorOffset = 12;

constexpr uint32_t MajorMask = 0x7FU;
constexpr uint32_t MinorMask = 0x3FFU;
constexpr uint32_t PatchMask = 0xFFFU;

Version::Version(uint8_t major, uint16_t minor, uint16_t patch)
	: version(static_cast<uint32_t>(0)
		| (static_cast<uint32_t>(major) << MajorOffset)
		| (static_cast<uint32_t>(minor) << MinorOffset)
		| static_cast<uint32_t>(patch)) { }

uint32_t Version::GetVersionNumber() const {
	return version;
}

uint8_t Version::GetMajor() const {
	return static_cast<uint8_t>((version >> MajorOffset) & MajorMask);
}

uint16_t Version::GetMinor() const {
	return static_cast<uint16_t>((version >> MinorOffset) & MinorMask);
}

uint16_t Version::GetPatch() const {
	return static_cast<uint16_t>(version & PatchMask);
}

uint16_t Version::GetRevision() const {
	return GetPatch();
}

std::string Version::GetVersionString() const {
	std::stringstream stream;
	stream << static_cast<uint16_t>(GetMajor()) << '.' << GetMinor() << '.' << GetPatch();
	return stream.str();
}

} // namespace Junia

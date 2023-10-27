#include <Junia/Core/Version.hpp>

#include <sstream>

namespace Junia {

constexpr std::uint32_t MajorOffset = 22;
constexpr std::uint32_t MinorOffset = 12;

constexpr std::uint32_t MajorMask = 0x7FU;
constexpr std::uint32_t MinorMask = 0x3FFU;
constexpr std::uint32_t PatchMask = 0xFFFU;

Version::Version(std::uint8_t major, std::uint16_t minor, std::uint16_t patch)
	: version(static_cast<std::uint32_t>(0)
		| (static_cast<std::uint32_t>(major) << MajorOffset)
		| (static_cast<std::uint32_t>(minor) << MinorOffset)
		| static_cast<std::uint32_t>(patch)) { }

std::uint32_t Version::GetVersionNumber() const {
	return version;
}

std::uint8_t Version::GetMajor() const {
	return static_cast<std::uint8_t>((version >> MajorOffset) & MajorMask);
}

std::uint16_t Version::GetMinor() const {
	return static_cast<std::uint16_t>((version >> MinorOffset) & MinorMask);
}

std::uint16_t Version::GetPatch() const {
	return static_cast<std::uint16_t>(version & PatchMask);
}

std::uint16_t Version::GetRevision() const {
	return GetPatch();
}

std::string Version::GetVersionString() const {
	std::stringstream stream;
	stream << static_cast<std::uint16_t>(GetMajor()) << '.' << GetMinor() << '.' << GetPatch();
	return stream.str();
}

} // namespace Junia

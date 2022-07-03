#pragma once
#include <string>

namespace Junia
{
	class Platform
	{
	public:
		static float GetTime();

		static std::string LoadFileAsString(const std::string& path);
		static std::string ReadFile(const std::string& filepath);
	};
}

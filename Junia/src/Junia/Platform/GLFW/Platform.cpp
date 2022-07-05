#ifdef JE_TARGETPLATFORM_GLFW

#include "../Platform.hpp"

#include <GLFW/glfw3.h>
#include <Junia/Core/Log.hpp>
#include <fstream>

namespace Junia
{
	float Junia::Platform::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}

	std::string Platform::LoadFileAsString(const std::string& path)
	{
		return ReadFile(path);
	}

	std::string Platform::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		} else JELOG_BASE_ERROR("File at " JELOG_CSTR " could not be loaded!", filepath.c_str());
		return result;
	}
}
#endif

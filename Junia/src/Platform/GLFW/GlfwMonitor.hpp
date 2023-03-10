#pragma once
#include <GLFW/glfw3.h>
#include <Junia/Core/Monitor.hpp>

namespace GLFW
{
	class GlfwMonitor : public Junia::Monitor
	{
	private:
		GLFWmonitor* monitor = nullptr;
		const GLFWvidmode* videoMode = nullptr;
		std::string name;

	public:
		GlfwMonitor(GLFWmonitor* monitor, size_t index);
		~GlfwMonitor();

		const std::string& GetName() const override;
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		uint32_t GetRedBits() const override;
		uint32_t GetGreenBits() const override;
		uint32_t GetBlueBits() const override;
		uint32_t GetRefreshRate() const override;
	};
}

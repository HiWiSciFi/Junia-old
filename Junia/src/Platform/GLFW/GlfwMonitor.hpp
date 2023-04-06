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
		JMath::Vec2ui GetPosition() const override;
		JMath::Vec2ui GetResolution() const override;
		JMath::Vec3ui GetColorBits() const override;
		uint32_t GetRefreshRate() const override;
		void* GetNative() const override;
	};
}

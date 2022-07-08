newoption {
	trigger = "opengl",
	description = "Enable support for rendering with OpenGL"
 }

 newoption {
	trigger = "vulkan",
	description = "Enable support for rendering with Vulkan (VulkanSDK has to be installed)"
 }

 newoption {
	trigger = "vulkanpath",
	value = "vlukansdk",
	description = "Path to VulkanSDK ($VULKAN_SDK)"
 }

 newoption {
	trigger = "windowapi",
	value = "API",
	description = "Choose a window manager to create windows with",
	allowed = {
		{ "native", "Platform native"       },
		{ "win32",  "Windows native"        },
		{ "glfw",   "GLFW (cross-platform)" }
	},
	default = "native"
 }

workspace "Junia"
	architecture "x86_64"
	startproject "Testing"

	configurations {
		"Debug",
		"Optimized",
		"Release"
	}

	defines {
		"JE_WINDOWAPI_GLFW=0",
		"JE_WINDOWAPI_WIN32=1",
		"JE_WINDOWAPI_X11=2"
	}

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE"
		}

	filter "configurations:Optimized"
		symbols "On"
		optimize "On"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_WARN"
		}

	filter "configurations:Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_ERROR"
		}

	filter { }

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	buildtargetname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	Dependency = {}

	include "Junia/premake-junia.lua"
	include "Testing/premake-testing.lua"

depsloc = "../Junia/dependencies/"

group "Dependencies"
	include "dependencies/premake-dependencies.lua"

group ""
project "Junia"
	location "."
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("../out/%{prj.name}/" .. buildtargetname)
	objdir ("../out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{Dependency.GLM.include}",
		"%{Dependency.stb.include}"
	}

	flags {
		"FatalCompileWarnings"
	}

	filter "options:opengl"
		defines "JE_GAPI_SUPPORTED_OPENGL"
		includedirs "%{Dependency.glad.include}"
		libdirs "%{Dependency.glad.libdir}"
		links {
			"opengl32",
			"glad"
		}

	filter "options:vulkan"
		defines "JE_GAPI_SUPPORTED_VULKAN"
		includedirs "%{Dependency.Vulkan.include}"
		libdirs "%{Dependency.Vulkan.libdir}"
		links "vulkan-1"

	filter "options:windowapi=glfw"
		defines "JE_WINDOWAPI=0"
		includedirs "%{Dependency.GLFW.include}"
		libdirs "%{Dependency.GLFW.libdir}"
		links "GLFW"

	filter "options:windowapi=win32"
		defines "JE_WINDOWAPI=1"
		links "windowsapp"

	filter { "system:windows", "options:windowapi=native" }
		defines "JE_WINDOWAPI=1"
		links "windowsapp"

	filter { not "system:windows", "options:windowapi=native" }
		defines "JE_WINDOWAPI=0"
		includedirs "%{Dependency.GLFW.include}"
		libdirs "%{Dependency.GLFW.libdir}"
		links "GLFW"

	filter "system:windows"
		systemversion "latest"
		defines "JE_TARGETPLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE"
		}

	filter "configurations:Optimized"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_WARN"
		}

	filter "configurations:Release"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_ERROR"
		}

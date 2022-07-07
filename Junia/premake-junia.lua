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

	defines {

	}

	includedirs {
		"src",
		"%{Dependency.Vulkan.include}",
		"%{Dependency.glad.include}",
		"%{Dependency.GLFW.include}",
		"%{Dependency.GLM.include}",
		"%{Dependency.stb.include}"
	}

	libdirs {
		"%{Dependency.Vulkan.libdir}",
		"%{Dependency.glad.libdir}",
		"%{Dependency.GLFW.libdir}"
	}

	links {
		"opengl32",
		"vulkan-1",
		"glad",
		"GLFW"
	}

	flags {
		"FatalCompileWarnings"
	}

	filter "system:windows"
		systemversion "latest"

		links {
			"windowsapp"
		}

		defines {
			"JE_TARGETPLATFORM_WINDOWS"
		}

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

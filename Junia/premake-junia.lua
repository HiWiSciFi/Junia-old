depsloc = "../Junia/dependencies/"

group "Dependencies"
	include "dependencies/premake-dependencies.lua"

group "Junia"
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
		"%{Dependency.GLFW.include}",
		"%{Dependency.spdlog.include}",
		"%{Dependency.GLM.include}"
	}

	libdirs {
		"%{Dependency.GLFW.libdir}",
		"%{Dependency.spdlog.libdir}"
	}

	links {
		"GLFW",
		"spdlog"
	}

	flags {
		"FatalWarnings"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"JE_TARGETPLATFORM_WINDOWS",
			"JE_EXPORT"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE"--,
			--"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Optimized"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_WARN"--,
			--"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_CRIT"
		}

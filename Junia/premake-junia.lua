depsloc = "../Junia/dependencies/"

group "Dependencies"
	include "dependencies/premake-dependencies.lua"

group "Junia"
project "Junia"
	location "."
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("../out/%{prj.name}/" .. buildtargetname)
	objdir ("../out-obj/%{prj.name}/" .. buildtargetname)

	pchheader "juniapch.hpp"
	pchsource "src/juniapch.cpp"

	files {
		"src/**.hpp",
		"src/**.cpp"
	}

	defines {

	}

	includedirs {
		"src",
		"%{Dependency.GLFW.include}",
		"%{Dependency.spdlog.include}"
	}

	libdirs {
		"%{Dependency.GLFW.lib}",
		"%{Dependency.spdlog.lib}"
	}

	links {
		"GLFW",
		"spdlog"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"JE_TARGETPLATFORM_WINDOWS",
			"JE_EXPORT"
		}
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../out/Testing/" .. buildtargetname)
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE",
			"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Optimized"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_ERROR",
			"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_CRIT"
		}
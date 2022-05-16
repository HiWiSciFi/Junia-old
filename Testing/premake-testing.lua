depsloc = "../Testing/dependencies/"

group "Dependencies"
	include "dependencies/premake-dependencies.lua"

group "Junia"
project "Testing"
	location "."
	kind "ConsoleApp"
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
		"../Junia/src",
		"%{Dependency.spdlog.include}"
	}

	libdirs {
		"%{Dependency.spdlog.lib}"
	}

	links {
		"Junia",
		"spdlog"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"JE_TARGETPLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"
		buildoptions "/MDd"
		defines {
			"JE_CONFIG_DEBUG",
			"JELOG_MAX_TRACE"--,
			--"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Optimized"
		runtime "Release"
		symbols "Off"
		optimize "On"
		buildoptions "/MDd"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_WARN"--,
			--"JELOG_EXTENDED_INFO"
		}

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
		buildoptions "/MDd"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_CRIT"
		}

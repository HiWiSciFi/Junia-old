workspace "Junia"
	architecture "x86_64"
	startproject "Testing"

	configurations {
		"Debug",
		"Optimized",
		"Release"
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

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	buildtargetname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	Dependency = {}

	include "Junia/premake-junia.lua"
	include "Testing/premake-testing.lua"
	
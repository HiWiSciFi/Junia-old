workspace "Junia"
	architecture "x86_64"
	startproject "Testing"

	configurations {
		"Debug",
		"Optimized",
		"Release"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	flags {
		"MultiProcessorCompile"
	}

	buildtargetname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	Dependency = {}

	include "Junia/premake-junia.lua"
	include "Testing/premake-testing.lua"
	
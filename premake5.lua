workspace "Junia"
	architecture "x86_64"
	startproject "Testing"

	configurations {
		"Debug",
		"Optimized",
		"Release"
	}

	flags {
		"MultiProcessorCompile",
		"RelativeLinks"
	}

	buildtargetname = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	Dependency = {}

	include "Junia/premake-junia.lua"
	include "Testing/premake-testing.lua"
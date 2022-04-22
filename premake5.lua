workspace "Junia"
	architecture "x86_64"
	startproject "Testing"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	include "Junia/premake-junia.lua"
	include "Testing/premake-testing.lua"
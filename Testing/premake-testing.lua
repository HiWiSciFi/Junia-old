project "Testing"
	location "."
	kind "ConsoleApp"
	language "C++"

	targetdir ("../out/" .. outputdir .. "/%{prj.name}")
	objdir ("../out-obj/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"../Junia/dependencies/spdlog/include",
		"../Junia/src"
	}

	links {
		"Junia"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"JE_PLATFORM_WINDOWS;"
		}

	filter "configurations:Debug"
		defines "JE_DEBUG"
		symbols "On"

	filter "configurations:Debug"
		defines "JE_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "JE_DIST"
		optimize "On"
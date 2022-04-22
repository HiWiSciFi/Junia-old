project "Junia"
	location "."
	kind "SharedLib"
	language "C++"

	targetdir ("../out/" .. outputdir .. "/%{prj.name}")
	objdir ("../out-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "juniapch.h"
	pchsource "src/juniapch.cpp"

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"dependencies/plog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"JE_PLATFORM_WINDOWS;",
			"JE_BUILD_DLL;"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../out/" .. outputdir .. "/Testing")
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
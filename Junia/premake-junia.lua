group "Dependencies"
	include "dependencies/premake-dependencies.lua"
group ""

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
		"%{Dependency.spdlog.include}"
	}

	links {
		
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
			"JELOG_MAX_TRACE",
			"JE_CONFIG_DEBUG"
		}

	filter "configurations:Optimized"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_OPTIMIZED",
			"JELOG_MAX_ERROR"
		}

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
		defines {
			"JE_CONFIG_RELEASE",
			"JELOG_MAX_CRIT"
		}
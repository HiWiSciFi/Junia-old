project "fmt"
	location "%{prj.name}"
	kind "None"
	language "C++"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/src/**.cc",
		"%{prj.name}/include/**.h"
	}

	includedirs {
		"%{prj.name}/include"
	}

	defines {
		"FMT_HEADER_ONLY"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Optimized"
		runtime "Release"
		symbols "Off"
		optimize "On"

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"

	filter {}
	Dependency["fmt"] = {}
	Dependency["fmt"]["include"] = depsloc .. "fmt/include"

project "stb"
	location "%{prj.name}"
	kind "None"
	language "C"

	files {
		"%{prj.name}/include/%{prj.name}/*.h"
	}

	includedirs {
		"%{prj.name}/include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		optimize "Off"

	filter "configurations:Optimized"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
	
	filter {}
		Dependency["stb"] = {}
		Dependency["stb"]["include"] = depsloc .. "stb/include"

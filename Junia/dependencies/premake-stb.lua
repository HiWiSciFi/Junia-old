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
	
	filter {}
		Dependency["stb"] = {}
		Dependency["stb"]["include"] = depsloc .. "stb/include"

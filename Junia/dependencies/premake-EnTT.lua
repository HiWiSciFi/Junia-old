project "EnTT"
	location "%{prj.name}"
	kind "None"
	language "C++"
	staticruntime "Off"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp"
	}

	includedirs {
		"%{prj.name}/single_include"
	}
	
	filter {}
		Dependency["EnTT"] = {}
		Dependency["EnTT"]["include"] = depsloc .. "EnTT/single_include"
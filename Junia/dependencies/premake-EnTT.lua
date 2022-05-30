project "EnTT"
	location "%{prj.name}"
	kind "None"
	language "C++"

	files {
		"%{prj.name}/%{prj.name}/src/**.h",
		"%{prj.name}/%{prj.name}/src/**.hpp"
	}

	includedirs {
		"%{prj.name}/%{prj.name}/single_include"
	}
	
	filter {}
		Dependency["EnTT"] = {}
		Dependency["EnTT"]["include"] = depsloc .. "EnTT/EnTT/single_include"
		
project "GLM"
	location "%{prj.name}"
	kind "None"
	language "C++"

	files {
		"%{prj.name}/%{prj.name}/glm/**.hpp",
		"%{prj.name}/%{prj.name}/glm/**.h"
	}

	includedirs {
		"%{prj.name}/%{prj.name}"
	}
	
	filter {}
		Dependency["GLM"] = {}
		Dependency["GLM"]["include"] = depsloc .. "GLM/GLM"
		
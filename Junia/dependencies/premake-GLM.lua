project "GLM"
	location "%{prj.name}"
	kind "None"
	language "C++"
	staticruntime "Off"

	files {
		"%{prj.name}/glm/**.hpp",
		"%{prj.name}/glm/**.h"
	}

	includedirs {
		"%{prj.name}"
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
		Dependency["GLM"] = {}
		Dependency["GLM"]["include"] = depsloc .. "GLM"
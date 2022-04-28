project "glad"
	location "%{prj.name}"
	kind "StaticLib"
	language "C"
	staticruntime "Off"

	pic "On"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.c"
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
		symbols "Off"
		optimize "On"

	filter "configurations:Release"
		runtime "Release"
		symbols "Off"
		optimize "On"
	
	filter {}
		Dependency["glad"] = {}
		Dependency["glad"]["include"] = depsloc .. "glad/include"
		Dependency["glad"]["libdir"] = depsloc .. "out/glad/" .. buildtargetname
project "glad"
	location "%{prj.name}"
	kind "StaticLib"
	language "C"
	staticruntime "On"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.c"
	}

	includedirs {
		"%{prj.name}/include"
	}

	filter {}
		Dependency["glad"] = {}
		Dependency["glad"]["include"] = depsloc .. "glad/include"
		Dependency["glad"]["libdir"] = depsloc .. "out/glad/" .. buildtargetname

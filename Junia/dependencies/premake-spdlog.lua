project "spdlog"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	files {
		"%{prj.name}/inlude/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/include"
	}

	defines {
		"SPDLOG_COMPILED_LIB"
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
		Dependency["spdlog"] = {}
		Dependency["spdlog"]["include"] = depsloc .. "spdlog/include"
		Dependency["spdlog"]["libdir"] = depsloc .. "out/spdlog/" .. buildtargetname

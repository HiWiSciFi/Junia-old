project "spdlog"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	files {
		"%{prj.name}/src/async.cpp",
		"%{prj.name}/src/cfg.cpp",
		"%{prj.name}/src/color_sinks.cpp",
		"%{prj.name}/src/file_sinks.cpp",
		"%{prj.name}/src/fmt.cpp",
		"%{prj.name}/src/spdlog.cpp",
		"%{prj.name}/src/stdout_sinks.cpp"
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

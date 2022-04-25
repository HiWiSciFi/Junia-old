project "spdlog"
	location "spdlog"
	kind "None"
	language "C++"
	cppdialect "C++17"

	files {
		"%{prj.name}/include/spdlog/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/include"
	}

	filter {}
		Dependency["spdlog"] = {}
		Dependency["spdlog"]["include"] = depsloc .. "spdlog/include"

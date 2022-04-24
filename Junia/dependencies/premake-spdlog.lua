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

Dependency["spdlog"] = {}
Dependency["spdlog"]["include"] = "../Junia/dependencies/spdlog/include"
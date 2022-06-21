project "imgui"
    location "%{prj.name}"
	kind "StaticLib"
	language "C++"
    staticruntime "On"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/%{prj.name}/imconfig.h",
		"%{prj.name}/%{prj.name}/imgui.h",
		"%{prj.name}/%{prj.name}/imgui.cpp",
		"%{prj.name}/%{prj.name}/imgui_draw.cpp",
		"%{prj.name}/%{prj.name}/imgui_internal.h",
		"%{prj.name}/%{prj.name}/imgui_tables.cpp",
		"%{prj.name}/%{prj.name}/imgui_widgets.cpp",
		"%{prj.name}/%{prj.name}/imstb_rectpack.h",
		"%{prj.name}/%{prj.name}/imstb_textedit.h",
		"%{prj.name}/%{prj.name}/imstb_truetype.h",
		"%{prj.name}/%{prj.name}/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

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
		Dependency["imgui"] = {}
		Dependency["imgui"]["include"] = depsloc .. "imgui/imgui"
		Dependency["imgui"]["libdir"] = depsloc .. "out/imgui/" .. buildtargetname

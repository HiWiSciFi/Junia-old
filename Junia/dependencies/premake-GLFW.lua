project "GLFW"
	location "%{prj.name}"
	kind "StaticLib"
	language "C"
	staticruntime "Off"

	pic "On"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/include/GLFW/glfw3.h",
		"%{prj.name}/include/GLFW/glfw3native.h",
		"%{prj.name}/src/glfw_config.h",
		"%{prj.name}/src/context.c",
		"%{prj.name}/src/init.c",
		"%{prj.name}/src/input.c",
		"%{prj.name}/src/monitor.c",

		"%{prj.name}/src/null_init.c",
		"%{prj.name}/src/null_joystick.c",
		"%{prj.name}/src/null_monitor.c",
		"%{prj.name}/src/null_window.c",

		"%{prj.name}/src/platform.c",
		"%{prj.name}/src/vulkan.c",
		"%{prj.name}/src/window.c"
	}

	filter "system:windows"
		systemversion "latest"

		files {
			"%{prj.name}/src/win32_init.c",
			"%{prj.name}/src/win32_joystick.c",
			"%{prj.name}/src/win32_module.c",
			"%{prj.name}/src/win32_monitor.c",
			"%{prj.name}/src/win32_time.c",
			"%{prj.name}/src/win32_thread.c",
			"%{prj.name}/src/win32_window.c",
			"%{prj.name}/src/wgl_context.c",
			"%{prj.name}/src/egl_context.c",
			"%{prj.name}/src/osmesa_context.c"
		}

		defines {
			"_GLFW_WIN32"
		}

	filter "system:linux"
		systemversion "latest"

		files {
			"%{prj.name}/src/x11_init.c",
			"%{prj.name}/src/x11_monitor.c",
			"%{prj.name}/src/x11_window.c",
			"%{prj.name}/src/xkb_unicode.c",
			"%{prj.name}/src/linux_joystick.c",
			"%{prj.name}/src/posix_time.c",
			"%{prj.name}/src/posix_thread.c",
			"%{prj.name}/src/glx_context.c",
			"%{prj.name}/src/egl_context.c",
			"%{prj.name}/src/osmesa_context.c"
		}

		defines {
			"_GLFW_X11"
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
		Dependency["GLFW"] = {}
		Dependency["GLFW"]["include"] = depsloc .. "GLFW/include"
		Dependency["GLFW"]["libdir"] = depsloc .. "out/GLFW/" .. buildtargetname

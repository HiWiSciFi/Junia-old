project "freetype"
	location "%{prj.name}"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

	targetdir ("out/%{prj.name}/" .. buildtargetname)
	objdir ("out-obj/%{prj.name}/" .. buildtargetname)

	files {
		"%{prj.name}/src/autofit/autofit.c",
		"%{prj.name}/src/bdf/bdf.c",
		"%{prj.name}/src/cff/cff.c",
		"%{prj.name}/src/base/ftbase.c",
		"%{prj.name}/src/base/ftbitmap.c",
		"%{prj.name}/src/cache/ftcache.c",
		"%{prj.name}/builds/windows/ftdebug.c",
		"%{prj.name}/src/base/ftfstype.c",
		"%{prj.name}/src/base/ftglyph.c",
		"%{prj.name}/src/gzip/ftgzip.c",
		"%{prj.name}/src/base/ftinit.c",
		"%{prj.name}/src/lzw/ftlzw.c",
		"%{prj.name}/src/base/ftstroke.c",
		"%{prj.name}/src/base/ftsystem.c",
		"%{prj.name}/src/smooth/smooth.c",

		"%{prj.name}/src/base/ftbbox.c",
		"%{prj.name}/src/base/ftgxval.c",
		"%{prj.name}/src/base/ftlcdfil.c",
		"%{prj.name}/src/base/ftmm.c",
		"%{prj.name}/src/base/ftotval.c",
		"%{prj.name}/src/base/ftpatent.c",
		"%{prj.name}/src/base/ftpfr.c",
		"%{prj.name}/src/base/ftsynth.c",
		
		--"%{prj.name}/src/base/ftxf86.c",
		"%{prj.name}/src/sdf/ftsdf.c",
		"%{prj.name}/src/sdf/ftbsdf.c",
		"%{prj.name}/src/sdf/ftsdfrend.c",
		"%{prj.name}/src/sdf/ftsdfcommon.c",
		"%{prj.name}/src/svg/ftsvg.c",
		
		"%{prj.name}/src/base/ftfstype.c",
		"%{prj.name}/src/pcf/pcf.c",
		"%{prj.name}/src/pfr/pfr.c",
		"%{prj.name}/src/psaux/psaux.c",
		"%{prj.name}/src/pshinter/pshinter.c",
		"%{prj.name}/src/psnames/psmodule.c",
		"%{prj.name}/src/raster/raster.c",
		"%{prj.name}/src/sfnt/sfnt.c",
		"%{prj.name}/src/truetype/truetype.c",
		"%{prj.name}/src/type1/type1.c",
		"%{prj.name}/src/cid/type1cid.c",
		"%{prj.name}/src/type42/type42.c",
		"%{prj.name}/src/winfonts/winfnt.c",      
    }

	includedirs {
		"%{prj.name}/include"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines {
			"WIN32",
			"WIN32_LEAN_AND_MEAN",
			"VC_EXTRALEAN",
			"_CRT_SECURE_NO_WARNINGS",
			"FT2_BUILD_LIBRARY",      
		}

	filter {}
		Dependency["freetype"] = {}
		Dependency["freetype"]["include"] = depsloc .. "freetype/include"
		Dependency["freetype"]["libdir"] = depsloc .. "out/freetype" .. buildtargetname

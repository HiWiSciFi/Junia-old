filter "options:opengl"
    include "premake-glad.lua"

filter "options:vulkan"
    include "premake-vulkan.lua"

filter "options:windowapi=glfw"
    include "premake-GLFW.lua"

filter {}
include "premake-EnTT.lua"
include "premake-GLM.lua"
include "premake-stb.lua"
include "premake-freetype.lua"

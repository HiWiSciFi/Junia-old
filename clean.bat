@echo off
DEL /F /Q .\Junia.sln
DEL /F /Q .\Junia\dependencies\glad\glad.vcxproj
DEL /F /Q .\Junia\dependencies\glad\glad.vcxproj.filters
DEL /F /Q .\Junia\dependencies\GLFW\GLFW.vcxproj
DEL /F /Q .\Junia\dependencies\GLFW\GLFW.vcxproj.filters
DEL /F /Q .\Junia\dependencies\EnTT\EnTT.vcxproj
DEL /F /Q .\Junia\dependencies\EnTT\EnTT.vcxproj.filters
DEL /F /Q .\Junia\dependencies\GLM\GLM.vcxproj
DEL /F /Q .\Junia\dependencies\GLM\GLM.vcxproj.filters
DEL /F /Q .\Junia\dependencies\stb\stb.vcxproj
DEL /F /Q .\Junia\Junia.vcxproj
DEL /F /Q .\Junia\Junia.vcxproj.filters
DEL /F /Q .\Testing\Testing.vcxproj
RD /S /Q .\out
RD /S /Q .\out-obj
RD /S /Q .\Junia\dependencies\out
RD /S /Q .\Junia\dependencies\out-obj

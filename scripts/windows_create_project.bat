@ECHO OFF
SETLOCAL EnableDelayedExpansion

IF /I "%1" == "--help" GOTO _help
IF /I "%1" == "-h"     GOTO _help
IF /I "%1" == "-?"     GOTO _help
IF /I "%1" == "/h"     GOTO _help
IF /I "%1" == "/help"  GOTO _help
IF /I "%1" == "/?"     GOTO _help

SET project-name=%1
IF /I "%project-name%" == "" SET /P "project-name=Enter project name: "
ECHO Project name set: %project-name%

ECHO ---- Creating Files -----
mkdir "%project-name%"
cd "%project-name%"
mkdir src
mkdir dependencies
mkdir build
TYPE NUL > "CMakeLists.txt"
TYPE NUL > ".gitignore"
TYPE NUL > "src/Main.cpp"

ECHO ----- Creating Git Repository -----
git init
git submodule add https://github.com/HiWiSciFi/Junia.git dependencies/Junia
git submodule update --init --recursive

ECHO ----- Populating .gitignore -----
>".gitignore" (
	ECHO build/
	ECHO out/
	ECHO:
	ECHO .vs/
)

ECHO ----- Populating CMakeLists.txt -----
>"CMakeLists.txt" (
	ECHO cmake_minimum_required(VERSION 3.20^)
	ECHO:
	ECHO project(%project-name% VERSION 1.0.0 LANGUAGES CXX^)
	ECHO:
	ECHO add_executable(%project-name%^)
	ECHO add_subdirectory("dependencies/Junia"^)
	ECHO add_dependencies(%project-name% Junia^)
	ECHO:
	ECHO set_target_properties(%project-name%
	ECHO 	PROPERTIES
	ECHO 		CXX_STANDARD 20
	ECHO 		CXX_STANDARD_REQUIRED "ON"
	ECHO ^)
	ECHO:
	ECHO target_link_libraries(%project-name%
	ECHO 	PRIVATE
	ECHO 		Junia
	ECHO ^)
	ECHO:
	ECHO target_include_directories(%project-name%
	ECHO 	PUBLIC
	ECHO 		"dependencies/Junia/Junia/include"
	ECHO ^)
	ECHO:
	ECHO target_sources(%project-name%
	ECHO 	PUBLIC
	ECHO 		"src/Main.cpp"
	ECHO ^)
	ECHO:
)

ECHO ----- Populating Main.cpp -----
>"src/Main.cpp" (
	ECHO #include ^<Junia.hpp^>
	ECHO:
	ECHO int main(int argc, char** argv^) {
	ECHO 	try {
	ECHO 		JELOG_INFO ^<^< "Initializing Junia...";
	ECHO 		Junia::Init(^);
	ECHO 		Junia::Renderer::PickDevice(nullptr^);
	ECHO 		JELOG_INFO ^<^< "Terminating Junia...";
	ECHO 		Junia::Terminate(^);
	ECHO 		JELOG_INFO ^<^< "Done.";
	ECHO 		return 0;
	ECHO 	} catch (std::exception exception^) {
	ECHO 		JELOG_CRITICAL ^<^< "Exception thrown: " ^<^< exception.what(^);
	ECHO 		Junia::ShowBlockingMessageBox(
	ECHO 			"%project-name%",
	ECHO 			exception.what(^),
	ECHO 			Junia::MessageBoxIcon::ERROR,
	ECHO 			Junia::MessageBoxButtons::OK
	ECHO 		^);
	ECHO 	}
	ECHO }
	ECHO:
)

ECHO ----- Testbuild -----
cd build
cmake ..
cmake --build .

ECHO ----- Testrun -----
cd Debug
.\%project-name%.exe
cd ..\..

ECHO ----- DONE -----

GOTO _end

:_help
ECHO Usage: windows_create_project [ ^<ProjectName^> ]
ECHO:
ECHO Parameters:
ECHO:
ECHO     ^<ProjectName^> : A project name that is valid for CMake targets.
ECHO                     It may only include [a-z], [A-Z], [0-9] and
ECHO                     ['_', '.', '+', '-']. Forbidden names include "clean",
ECHO                     "help", "install", "test" and "package". For more
ECHO                     information, see https://cmake.org/cmake/help/latest/policy/CMP0037.html
ECHO:

:_end
ENDLOCAL

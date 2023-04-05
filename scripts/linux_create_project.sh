#!/bin/bash

if [ "$1" = "--help" ] || [ "$1" = "-h" ] || [ "$1" = "-?" ]
then
	echo Usage: linux_create_project [ <ProjectName> ]
	echo
	echo Parameters:
	echo 
	echo     <ProjectName> : A project name that is valid for CMake targets.
	echo                     It may only include [a-z], [A-Z], [0-9] and
	echo                     ['_', '.', '+', '-']. Forbidden names include "clean",
	echo                     "help", "install", "test" and "package". For more
	echo                     information, see https://cmake.org/cmake/help/latest/policy/CMP0037.html
	echo
fi

projectName=$1

if [ "$projectName" = "" ]
then
	read -p "Enter project name: " projectName
fi

echo Project name set: $projectName

echo ----- Creating Files -----
mkdir $projectName
cd $projectName
mkdir src
mkdir dependencies
mkdir build
touch CMakeLists.txt
touch .gitignore
touch src/Main.cpp

echo ----- Creating Git Repository -----
git init
git submodule add https://github.com/HiWiSciFi/Junia.git dependencies/Junia
git submodule update --init --recursive

echo ----- Populating .gitignore -----
echo "build/
out/

.vs/
" >> .gitignore

echo ----- Populating CMakeLists.txt -----
echo "cmake_minimum_required(VERSION 3.20)

project($projectName VERSION 1.0.0 LANGUAGES CXX)

add_executable($projectName)
add_subdirectory(\"dependencies/Junia\")
add_dependencies($projectName Junia)

set_target_properties($projectName
	PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED \"ON\"
)

target_link_libraries($projectName
	PRIVATE
		Junia
)

target_include_directories($projectName
	PUBLIC
		\"dependencies/Junia/Junia/include\"
)

target_sources($projectName
	PUBLIC
		\"src/Main.cpp\"
)" >> CMakeLists.txt

echo ----- Populating Main.cpp -----
echo "#include <Junia.hpp>

int main(int argc, char** argv) {
	try {
		JELOG_INFO << \"Initializing Junia...\";
		Junia::Init();
		Junia::Renderer::PickDevice(nullptr);
		JELOG_INFO << \"Terminating Junia...\";
		Junia::Terminate();
		JELOG_INFO << \"Done.\";
		return 0;
	} catch (std::exception exception) {
		JELOG_CRITICAL << \"Exception thrown: \" << exception.what();
		Junia::ShowBlockingMessageBox(
			\"$projectName\",
			exception.what(),
			Junia::MessageBoxIcon::ERROR,
			Junia::MessageBoxButtons::OK
		);
	}
}" >> src/Main.cpp

echo ----- Testbuild -----
cd build
cmake ..
cmake --build .

echo ----- Testrun -----
./$projectName
cd ../..

echo ----- DONE -----

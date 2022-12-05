#include "Editor.hpp"
#include <Junia.hpp>

#include <iostream>

void RunGame()
{
	Junia::Window window;
	while (!window.shouldClose)
	{
		window.Update();
	}
}

int main(int argc, char** argv)
{
	//Junia::Log::log.maxLevel = Junia::Log::LogLevel::Warn;
	//Junia::Log::corelog.maxLevel = Junia::Log::LogLevel::Warn;

	JELOG_INFO << "Initializing Junia...";
	Junia::Init();
	JELOG_INFO << "Creating Window...";
	RunGame();
	JELOG_INFO << "Terminating Junia...";
	Junia::Terminate();
	JELOG_INFO << "Done.";
	return 0;
}

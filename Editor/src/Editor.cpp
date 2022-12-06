#include "Editor.hpp"
#include <Junia.hpp>

#include <iostream>

void RunGame()
{
	Junia::Window window;
	Junia::Window window2;
	while (!window.shouldClose)
	{
		for (int i = 1; i < Junia::Window::GetWindowCount(); i++)
			Junia::Window::GetWindow(i)->Update();
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

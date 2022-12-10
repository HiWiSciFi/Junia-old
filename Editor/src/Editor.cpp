#include "Editor.hpp"
#include <Junia.hpp>
#include <iostream>

void RunGame()
{
	Junia::Window* window = Junia::Window::CreateWindow();
	Junia::Window* window2 = Junia::Window::CreateWindow();
	JELOG_WARN << "Remaining windows: " << Junia::Window::GetWindowCount();
	while (!window->shouldClose)
	{
		for (int i = 1; i < Junia::Window::GetWindowCount() + 1; i++)
			Junia::Window::GetWindow(i)->Update();
		if (window2 != nullptr && window2->shouldClose)
		{
			Junia::Window::DestroyWindow(window2);
			JELOG_WARN << "Remaining windows: " << Junia::Window::GetWindowCount();
			window2 = nullptr;
		}
	}
	Junia::Window** const windows = Junia::Window::GetWindows();
	for (int i = Junia::Window::GetWindowCount(); i > 0; i--)
		Junia::Window::DestroyWindow(windows[i]);
	JELOG_WARN << "Remaining windows: " << Junia::Window::GetWindowCount();
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

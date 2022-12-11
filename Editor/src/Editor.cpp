#include "Editor.hpp"
#include <Junia.hpp>
#include <iostream>

void RunGame()
{
	Junia::Window::Create("First Window ©")->Open();
	Junia::Window::Create("Second Window")->Open();
	JELOG_WARN << "Remaining windows: " << Junia::Window::GetWindowCount();
	while (Junia::Window::GetWindow(0)->IsOpen())
	{
		for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
		{
			if (Junia::Input::IsKeyDown(Junia::KeyCode::ESCAPE, i))
				Junia::Window::GetWindow(i)->Close();
			Junia::Window::GetWindow(i)->Update();
		}
	}
	Junia::Window** const windows = Junia::Window::GetWindows();
	for (Junia::Window::IdType i = Junia::Window::GetWindowCount(); i > 0; i--)
		Junia::Window::Destroy(windows[i]);
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

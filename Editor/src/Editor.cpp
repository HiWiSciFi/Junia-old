#include "Editor.hpp"
#include <Junia.hpp>
#include <iostream>

void RunGame()
{
	Junia::Window* mainWindow = Junia::Window::Create("First Window");
	mainWindow->Open();
	Junia::Window::Create("Second Window")->Open();
	mainWindow->Focus();

	while (mainWindow->IsOpen())
	{
		for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
			Junia::Window::GetWindow(i)->Update();

		if (Junia::Input::IsKeyDown(Junia::KeyCode::ESCAPE))
			Junia::Window::GetWindow()->Close();
	}

	Junia::Window** const windows = Junia::Window::GetWindows();
	for (Junia::Window::IdType i = Junia::Window::GetWindowCount(); i > 0; i--)
		Junia::Window::Destroy(windows[i]);
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

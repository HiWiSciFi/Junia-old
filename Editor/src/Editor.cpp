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
	std::shared_ptr<Junia::Logger> logger = Junia::Logger::Create("YeetusLoggus");

	logger->Trace() << "Helo mah boii";
	logger->Info() << "This is informative";
	logger->Warn() << "A warning apparently";
	logger->Error() << "Oopsies that didn't sound good...";
	logger->Critical() << "your code is now broken";

	Junia::Init();

	RunGame();

	Junia::Terminate();
	return 0;
}

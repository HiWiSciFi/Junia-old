#include "Junia/Junia.h"
#include "Lvl0.h"

int main(int argc, char* argv[]) {
	Junia::init();

	Window* application = Junia::createWindow();
	Canvas* levelDisplay = application->addGuiElement<Canvas>();
	Lvl0* lvl0 = levelDisplay->loadLevel<Lvl0>();

	while (Junia::running) Junia::gameLoop();
	
	Junia::quit();
	return 0;
}
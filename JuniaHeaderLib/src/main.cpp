#include "Junia/Junia.h"
#include "Lvl0.h"

int main(int argc, char* argv[]) {
	if (Junia::init() != 0) {
		Junia::log("Junia could not be initialized!");
		return 1;
	}

	Window* game = Junia::createWindow();
	Canvas* levelManager = game->addGuiElement<Canvas>();
	Level* lvl0 = levelManager->loadLevel<Lvl0>();

	Junia::log("Junia initialized and loaded!");

	while (Junia::running) Junia::gameLoop();

	Junia::quit();

	return 0;
}
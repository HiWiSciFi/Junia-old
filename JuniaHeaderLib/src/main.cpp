#include "Junia/Junia.h"
#include "Lvl0.h"

#include <iostream>

int main(int argc, char* argv[]) {
	if (Junia::init() != 0) {
		Junia::log("Junia could not be initialized!");
		return 1;
	}

	Window* game = Junia::createWindow();
	Level* lvl0 = new Lvl0();
	Canvas* canvas = game->addGuiElement<Canvas>(lvl0);

	while (Junia::running) Junia::gameLoop();

	delete game;
	Junia::quit();

	return 0;
}
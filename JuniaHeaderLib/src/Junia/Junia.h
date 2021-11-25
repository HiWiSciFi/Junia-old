#ifndef _JUNIA_H
#define _JUNIA_H

#include <SDL.h>
#include "GUI.h"
#include "ECS.h"
#include "DefaultComponents.h"
#include "Level.h"

#include <list>

namespace Junia {
	std::list<Window*> windows;
	bool running = false;

	int init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			// successful
			running = true;
			return 0;
		}
		return 1;
	}

	Window* createWindow(const char* title = "Junia Window", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 800, int height = 600) {
		Window* window = new Window(title, x, y, width, height);
		windows.push_back(window);
		return window;
	}

	void log(const char* message) {
		SDL_Log(message);
	}

	void quit() {
		running = false;
		for (Window*& w : windows) {
			w->running = false;
		}
		for (Window*& w : windows) {
			delete w;
		}
	}

	void gameLoop() {
		// called on every iteration
		for (Window*& w : windows) {
			w->gameLoop();
		}
	}
}

#endif // _JUNIA_H
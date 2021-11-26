#ifndef _JUNIABASE_H
#define _JUNIABASE_H

#include "GUI/Window.h"
#include <SDL.h>
#include <vector>
#include <algorithm>

namespace Junia {
	std::vector<Window*> windows;
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

	void clean() {
		for (Window*& w : windows) { w->running = false; }
		while (!windows.empty()) delete windows.back(), windows.pop_back();
	}

	void quit() {
		running = false;
		clean();
		SDL_Quit();
	}

	void destroyWindow(Window* w) {
		delete w;
		windows.erase(std::remove(windows.begin(), windows.end(), w), windows.end());
		if (windows.size() == 0) {
			quit();
		}
	}

	void gameLoop() {
		// handle events
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			destroyWindow(windows.front());
			break;
		}

		// called on every iteration
		for (Window*& w : windows) w->gameLoop();
	}
}

#endif // _JUNIABASE_H
#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL.h>
#include "../Level.h"
#include "GuiElement.h"
#include <list>
#include <string>

class Window : public GuiElement {
public:
	bool running = false;

	Window(const char* _title, int _x, int _y, int _width, int _height) {
		posX = _x;
		posY = _y;
		width = _width;
		height = _height;
		title = _title;

		window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		running = true;
	}

	~Window() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}

	void gameLoop() {
		for (GuiElement*& ge : guiElements) ge->update();
		for (GuiElement*& ge : guiElements) {
			SDL_RenderClear(renderer);
			ge->draw(renderer);
			SDL_RenderPresent(renderer);
		}
	}

	template <typename T, typename... TArgs>
	T* addGuiElement(TArgs... args) {
		T* ge = new T(std::forward<TArgs>(args)...);
		guiElements.push_back(ge);
		return ge;
	}

private:
	int posX;
	int posY;
	int width;
	int height;
	std::string title;

	std::list<GuiElement*> guiElements;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // _WINDOW_H
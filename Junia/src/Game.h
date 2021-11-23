#ifndef _GAME_H
#define _GAME_H

#include "SDL.h"
#include "SDL_image.h"

class Game {
public:
	Game();
	~Game();

	/// @brief initialize the window
	/// @param title window title
	/// @param x window position x coordinate
	/// @param y window position y coordinate
	/// @param width the window length along the x axis
	/// @param height the window length along the y axis
	/// @param fullscreen if the window should be initialized in fullscreen
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	/// @brief handle pending events
	void handleEvents();
	/// @brief update objects, scripts, etc
	void update();
	/// @brief render what has changed
	void render();
	/// @brief cleanup calls
	void clean();

	/// @brief check if the application is still running
	/// @return true, if the application is running, otherwise false
	bool running() { return isRunning; }

	static SDL_Renderer* renderer;

private:
	/// @brief if the game loop associated with the window is still running
	bool isRunning;
	/// @brief the pointer to the sdl window to draw to
	SDL_Window* window;
};

#endif // _GAME_H
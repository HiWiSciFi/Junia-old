#ifndef _CANVAS_H
#define _CANVAS_H

#include "GuiElement.h"

class Canvas : public GuiElement {
public:
	Canvas() {
		parent = nullptr;
		currentLevel = new Level();
	}

	Canvas(Level* _level) {
		parent = nullptr;
		currentLevel = _level;
	}

	~Canvas() {
		delete currentLevel;
	}

	void loadLevel(Level* _level) {
		currentLevel->unload();
		currentLevel = _level;
		currentLevel->load();
	}

	void unloadLevel() {
		currentLevel->unload();
	}

	void onInit() override {

	}

	void onUpdate() override {

	}

	void onDraw(SDL_Renderer* renderer) override {
		currentLevel->draw();
	}

private:
	Level* currentLevel;
};

#endif // _CANVAS_H
#ifndef _CANVAS_H
#define _CANVAS_H

#include "GuiElement.h"
#include "../Level.h"

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
		unloadLevel();
	}

	template <typename T, typename... TArgs>
	T* loadLevel(TArgs... levelConstructorArgs) {
		T* level = new T(std::forward<TArgs>(levelConstructorArgs)...);
		unloadLevel();
		currentLevel = level;
		currentLevel->load();
		return level;
	}

	void unloadLevel() {
		currentLevel->unload();
		delete currentLevel;
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
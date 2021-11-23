#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Game.h"

class GameObject {
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

#endif // _GAMEOBJECT_H
#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif // _TEXTUREMANAGER_H
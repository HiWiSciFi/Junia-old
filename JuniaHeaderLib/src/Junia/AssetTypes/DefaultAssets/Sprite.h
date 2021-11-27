#ifndef _SPRITE_H
#define _SPRITE_H

#include "../Asset.h"
#include <SDL.h>
#include <SDL_image.h>

class Sprite : public Asset {
public:
	SDL_Rect* srcRect = nullptr;

	void loadFromPath(const char* path) override {
		texture = IMG_Load(path);
		srcRect = &texture->clip_rect;
	}

	void unload() override {
		SDL_FreeSurface(texture);
	}

	SDL_Texture* convertToTexture(SDL_Renderer* renderer) {
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, texture);
		return tex;
	}

private:
	SDL_Surface* texture;
};

#endif // _SPRITE_H
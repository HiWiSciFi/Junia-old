#ifndef _SPRITECOMPONENT_H
#define _SPRITECOMPONENT_H

#include "../ECS.h"
#include "TransformComponent.h"
#include "../../AssetTypes/DefaultAssets/Sprite.h"
#include <iostream>

class SpriteComponent : public Component {
public:
	Sprite* sprite;

	SpriteComponent() {
		transform = nullptr;
		sprite = nullptr;
		texture = nullptr;
		destRect = new SDL_Rect();
	}

	SpriteComponent(Sprite* _sprite) {
		transform = nullptr;
		sprite = _sprite;
		texture = nullptr;
		destRect = new SDL_Rect();
	}

	void onInit() {
		transform = entity->requireComponent<TransformComponent>(); // require Component
	}

	void onDraw(SDL_Renderer* renderer) {
		if (sprite != nullptr) {
			if (texture != nullptr) {
				SDL_RenderCopy(renderer, texture, sprite->srcRect, recalcDestRect());
			}
			else {
				// load texture from surface
				texture = sprite->convertToTexture(renderer);
			}
		}
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect* destRect;

	SDL_Rect* recalcDestRect() {
		destRect->w = sprite->srcRect->w * transform->xscale;
		destRect->h = sprite->srcRect->h * transform->yscale;
		destRect->x = transform->x;
		destRect->y = transform->y;
		return destRect;
	}
};

#endif // _SPRITECOMPONENT_H
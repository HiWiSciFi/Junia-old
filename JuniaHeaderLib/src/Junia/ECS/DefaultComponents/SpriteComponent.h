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
	}

	SpriteComponent(Sprite* _sprite) {
		transform = nullptr;
		sprite = _sprite;
		texture = nullptr;
	}

	void onInit() override {
		transform = entity->requireComponent<TransformComponent>(); // require Component
	}

	void onDraw(SDL_Renderer* renderer) override {
		if (sprite != nullptr) {
			if (texture != nullptr) {
				SDL_RenderCopy(renderer, texture, sprite->srcRect, &calcDestRect());
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

	SDL_Rect& calcDestRect() {
		SDL_Rect rect;
		rect.w = sprite->srcRect->w * transform->xscale;
		rect.h = sprite->srcRect->h * transform->yscale;
		rect.x = transform->x;
		rect.y = transform->y;
		return rect;
	}
};

#endif // _SPRITECOMPONENT_H
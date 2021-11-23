#ifndef _SPRITECOMPONENT_H
#define _SPRITECOMPONENT_H

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		if (!entity->hasComponent<PositionComponent>()) entity->addComponent<PositionComponent>();
		position = &entity->getComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;
	}

	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

#endif // _SPRITECOMPONENT_H
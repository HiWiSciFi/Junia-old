#ifndef _LVL0_H
#define _LVL0_H

#include "Junia/Junia.h"

class Lvl0 : public Level {
public:
	void onLoad() override {
		Entity* entity = createEntity();
		Sprite* sprite = AssetManager::loadAssetFromPath<Sprite>("assets/player.png");
		SpriteComponent* sc = entity->addComponent<SpriteComponent>(sprite);
		TransformComponent* transform = entity->getComponent<TransformComponent>();
		transform->xscale = 2;
		transform->yscale = 2;
	}

	void onUnload() override {

	}
};

#endif // _LVL0_H
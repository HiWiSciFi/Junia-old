#ifndef _LVL0_H
#define _LVL0_H

#include "Junia/Junia.h"

class Lvl0 : public Level {
public:
	void onLoad() {
		Entity* entity = createEntity();
		entity->addComponent<SpriteComponent>(AssetManager::loadAssetFromPath<Sprite>("assets/player.png"));
		TransformComponent* transform = entity->getComponent<TransformComponent>();
		transform->xscale = 2;
		transform->yscale = 2;
	}

	void onUnload() {

	}
};

#endif // _LVL0_H
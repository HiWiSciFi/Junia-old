#ifndef _LVL0_H
#define _LVL0_H

#include "Junia/Junia.h"
#include "Junia/DefaultComponents.h"
#include <iostream>

class Lvl0 : public Level {
public:
	void onLoad() override {
		Entity* entity = createEntity();
		SpriteComponent* tc = entity->addComponent<SpriteComponent>();
		printf("%i", entity->getComponent<TransformComponent>()->x);
	}

	void onUnload() override {

	}
};

#endif // _LVL0_H
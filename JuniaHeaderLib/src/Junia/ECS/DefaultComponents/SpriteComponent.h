#ifndef _SPRITECOMPONENT_H
#define _SPRITECOMPONENT_H

#include "Junia/ECS.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() {
		transform = nullptr;
	}

	void onInit() override {
		transform = entity->requireComponent<TransformComponent>(); // require Component
	}

private:
	TransformComponent* transform;
};

#endif // _SPRITECOMPONENT_H
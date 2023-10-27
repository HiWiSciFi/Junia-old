#include "GravitySystem.hpp"

const float GravitySystem::downForce = 1.0f;

void GravitySystem::Init() {
	RequireComponent<Junia::Transform>();
}

void GravitySystem::Update(float dt) {
	for (auto& e : GetEntities()) {
		Junia::ComponentRef<Junia::Transform> transform = e.GetComponent<Junia::Transform>();
		transform->position.z -= this->downForce * dt;
	}
}

#include "GravitySystem.hpp"

float GravitySystem::downForce = -1.0f;

void GravitySystem::Init()
{
	RequireComponent<Junia::Transform>();
}

void GravitySystem::Update(float dt)
{
	for (auto const& e : entities)
	{
		Junia::Transform& transform = e.GetComponent<Junia::Transform>();
		transform.position.z -= downForce * dt;
	}
}

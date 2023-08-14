#include "GravitySystem.hpp"

const float GravitySystem::downForce = -1.0f;

void GravitySystem::Init()
{
	RequireComponent<Junia::Transform>();
}

void GravitySystem::Update(float dt)
{
	for (auto const& e : GetEntities())
	{
		Junia::Transform& transform = e.GetComponent<Junia::Transform>();
		transform.position.z -= downForce * dt;
	}
}

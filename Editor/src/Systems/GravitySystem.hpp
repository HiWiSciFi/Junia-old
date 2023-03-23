#pragma once

#include <Junia.hpp>

class GravitySystem : public Junia::ECS::System
{
private:
	static const float downForce;

public:
	void Init() override;
	void Update(float dt) override;
};

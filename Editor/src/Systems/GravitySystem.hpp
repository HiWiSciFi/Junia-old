#pragma once

#include <Junia.hpp>

class GravitySystem : public Junia::System {
private:
	static const float downForce;

public:
	void Init() override;
	void Update(float delta) override;
};

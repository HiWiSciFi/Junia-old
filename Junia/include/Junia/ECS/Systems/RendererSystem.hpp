#pragma once

#include "../../ECS/ECS.hpp"

namespace Junia {

class RendererSystem : public System {
public:
	void Init() override;
	void Update(float delta) override;
};

} // namespace Junia

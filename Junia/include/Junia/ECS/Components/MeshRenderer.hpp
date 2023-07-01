#pragma once

#include "../../Renderer/Mesh.hpp"
#include "../../Renderer/Material.hpp"

namespace Junia {

struct MeshRenderer {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};

} // namespace Junia

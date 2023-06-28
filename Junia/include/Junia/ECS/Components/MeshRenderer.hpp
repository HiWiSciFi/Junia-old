#pragma once

#include "../../Renderer/Mesh.hpp"
#include "../../Renderer/Material.hpp"
#include "../../Renderer/RenderPackage.hpp"

namespace Junia {

struct MeshRenderer {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
	std::shared_ptr<RenderPackage> package = nullptr;
};

} // namespace Junia

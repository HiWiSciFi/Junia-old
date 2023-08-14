#pragma once

#include "../../Renderer/Mesh.hpp"
#include "../../Renderer/Material.hpp"
#include "../ECS.hpp"

namespace Junia {

struct MeshRenderer : public Component {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;

	MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
		: mesh(mesh), material(material) { }
};

} // namespace Junia

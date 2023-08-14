#pragma once

#include <Junia.hpp>
#include <string>

class Scene1 : public Junia::Scene {
private:
	std::shared_ptr<Junia::Mesh> squareMesh;
	std::shared_ptr<Junia::Mesh> triangleMesh;
	std::shared_ptr<Junia::Material> squareMaterial;

public:
	explicit Scene1();
	~Scene1() override;
};

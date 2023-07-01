#include "Scene1.hpp"
#include <Junia.hpp>

Scene1::Scene1() {
	squareMesh = Junia::Mesh::Create("Assets/Models/Square.obj", Junia::Mesh::FileType::OBJ);
	std::shared_ptr<Junia::Shader> vertShader = Junia::Shader::Create("Assets/Shaders/shader2_vert.spv", Junia::Shader::Type::VERTEX);
	std::shared_ptr<Junia::Shader> fragShader = Junia::Shader::Create("Assets/Shaders/shader2_frag.spv", Junia::Shader::Type::FRAGMENT);
	squareMaterial = Junia::Material::Create(vertShader, fragShader);

	Junia::ECS::Entity square = Junia::ECS::Entity::Create();
	square.AddComponent<Junia::Transform>();
	Junia::Transform& transform = square.GetComponent<Junia::Transform>();
	transform.position = JMath::Vec3(0.0f, 0.0f, 0.0f);
	transform.rotation = JMath::Vec3(0.0f, 0.0f, 0.0f);
	transform.scale = JMath::Vec3(1.0f, 1.0f, 1.0f);
	square.AddComponent<Junia::MeshRenderer>();
	Junia::MeshRenderer& renderer = square.GetComponent<Junia::MeshRenderer>();
	renderer.mesh = squareMesh;
	renderer.material = squareMaterial;
}

Scene1::~Scene1() {
}

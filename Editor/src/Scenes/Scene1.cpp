#include "Scene1.hpp"
#include <Junia.hpp>
#include <JMath/Matrix4x4.hpp>

struct UniformBufferObject {
	JMath::Mat4 model;
	JMath::Mat4 view;
	JMath::Mat4 proj;
};

Scene1::Scene1() {
	squareMesh = Junia::Mesh::Create("Assets/Models/Square.obj", Junia::Mesh::FileType::OBJ);
	triangleMesh = Junia::Mesh::Create("Assets/Models/Triangle.obj", Junia::Mesh::FileType::OBJ);
	std::shared_ptr<Junia::Shader> vertShader = Junia::Shader::Create("Assets/Shaders/shader2_vert.spv", Junia::Shader::Type::VERTEX);
	std::shared_ptr<Junia::Shader> fragShader = Junia::Shader::Create("Assets/Shaders/shader2_frag.spv", Junia::Shader::Type::FRAGMENT);
	squareMaterial = Junia::Material::Create(vertShader, fragShader);

	Junia::Entity square = Junia::Entity::Create();
	Junia::Transform& squareTransform = square.AddComponent<Junia::Transform>(
		JMath::Vec3(0.0f, 0.0f, 0.0f),
		JMath::Vec3(0.0f, 0.0f, 0.0f),
		JMath::Vec3(1.0f, 1.0f, 1.0f));
	Junia::MeshRenderer& squareRenderer = square.AddComponent<Junia::MeshRenderer>(
		squareMesh,
		squareMaterial);

	Junia::Entity triangle = Junia::Entity::Create();
	Junia::Transform& triangleTransform = triangle.AddComponent<Junia::Transform>(
		JMath::Vec3(0.0f, 0.0f, 0.0f),
		JMath::Vec3(0.0f, 0.0f, 0.0f),
		JMath::Vec3(1.0f, 1.0f, 1.0f));
	Junia::MeshRenderer& triangleRenderer = triangle.AddComponent<Junia::MeshRenderer>(
		triangleMesh,
		squareMaterial);
}

Scene1::~Scene1() {
}

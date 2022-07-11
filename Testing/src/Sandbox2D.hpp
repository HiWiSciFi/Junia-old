#pragma once

#include <Junia.hpp>
#include <Junia/OrthographicCameraController.hpp>

class Sandbox2D : public Junia::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;

	void OnEnable() override;
	void OnDisable() override;
	void OnUpdate(const Junia::Timestep& deltaTime) override;

private:
	Junia::Ref<Junia::Shader> flatColorShader;
	Junia::Ref<Junia::VertexArray> squareVa;
	Junia::OrthographicCameraController cameraController;

	glm::vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

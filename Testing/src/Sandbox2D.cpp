#include "Sandbox2D.hpp"

#include <Junia/Platform/OpenGL/OpenGLShader.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnEnable()
{

}

void Sandbox2D::OnDisable()
{
}

void Sandbox2D::OnUpdate(const Junia::Timestep& deltaTime)
{
	cameraController.OnUpdate(deltaTime);

	Junia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Junia::RenderCommand::Clear();

	Junia::Renderer2D::BeginScene(cameraController.GetCamera());

	Junia::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	Junia::Renderer2D::EndScene();
}

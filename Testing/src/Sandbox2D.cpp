#include "Sandbox2D.hpp"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnEnable()
{
	checkerboardTexture = Junia::Texture2D::Create("assets/textures/Checkerboard.png");
	font = Junia::Font::Create("assets/fonts/Roboto-Black.ttf");
	//font = Junia::Font::Create("assets/fonts/Caskaydia Cove Nerd Font Complete.ttf");
	helloWorldTexture = font->GetTextureFromString("Hello World!");
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

	Junia::Renderer2D::DrawQuad({ -1.0f,  0.0f }, {  0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Junia::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
	Junia::Renderer2D::DrawQuad({  0.5f, -0.5f }, {  0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Junia::Renderer2D::DrawRotatedQuad({  0.0f,  0.0f, -.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), checkerboardTexture, 10.0f);
	Junia::Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 6.0f, 1.0f }, helloWorldTexture, 1.0f, { 1.0f, 0.0f, 0.0f, 1.0f });

	Junia::Renderer2D::EndScene();
}

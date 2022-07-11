#include "Sandbox2D.hpp"

#include <Junia/Platform/OpenGL/OpenGLShader.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnEnable()
{
	squareVa = Junia::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f
	};

	Junia::Ref<Junia::VertexBuffer> squareVb = Junia::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVb->SetLayout({
		{ Junia::ShaderDataType::Float3, "inPosition" }
	});
	squareVa->AddVertexBuffer(squareVb);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Junia::Ref<Junia::IndexBuffer> squareIb = Junia::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	squareVa->SetIndexBuffer(squareIb);

	flatColorShader = Junia::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDisable()
{
}

void Sandbox2D::OnUpdate(const Junia::Timestep& deltaTime)
{
	cameraController.OnUpdate(deltaTime);

	Junia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Junia::RenderCommand::Clear();

	Junia::Renderer::BeginScene(cameraController.GetCamera());

	// TODO: Add functions: Shader::SetMat4, Shader::SetFloat4
	flatColorShader->Bind();
	std::dynamic_pointer_cast<Junia::OpenGLShader>(flatColorShader)->UploadUniformFloat4("u_Color", squareColor);

	Junia::Renderer::Submit(flatColorShader, squareVa, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Junia::Renderer::EndScene();
}

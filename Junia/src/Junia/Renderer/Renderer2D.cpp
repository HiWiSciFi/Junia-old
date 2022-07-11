#include "Renderer2D.hpp"
#include <Junia/Renderer/VertexArray.hpp>
#include <Junia/Renderer/Shader.hpp>
#include <Junia/Renderer/RenderCommand.hpp>

#include <Junia/Platform/OpenGL/OpenGLShader.hpp>

namespace Junia
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
	};

	static Renderer2DStorage* rendererData;

	void Renderer2D::Init()
	{
		rendererData = new Renderer2DStorage();

		rendererData->vertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f
		};

		Ref<VertexBuffer> squareVb = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVb->SetLayout({
			{ ShaderDataType::Float3, "inPosition" }
		});
		rendererData->vertexArray->AddVertexBuffer(squareVb);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIb = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		rendererData->vertexArray->SetIndexBuffer(squareIb);

		rendererData->shader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete rendererData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		rendererData->shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->shader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->shader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
		// YEET YEET USELESS CALLLLL
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		rendererData->shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->shader)->UploadUniformFloat4("u_Color", color);
		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
}

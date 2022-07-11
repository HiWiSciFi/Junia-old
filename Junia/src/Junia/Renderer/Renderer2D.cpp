#include "Renderer2D.hpp"
#include <Junia/Renderer/VertexArray.hpp>
#include <Junia/Renderer/Shader.hpp>
#include <Junia/Renderer/RenderCommand.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Junia
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DStorage* rendererData;

	void Renderer2D::Init()
	{
		rendererData = new Renderer2DStorage();

		rendererData->vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVb = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVb->SetLayout({
			{ ShaderDataType::Float3, "inPosition" },
			{ ShaderDataType::Float2, "inTexCoord" }
		});
		rendererData->vertexArray->AddVertexBuffer(squareVb);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIb = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		rendererData->vertexArray->SetIndexBuffer(squareIb);

		rendererData->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
		rendererData->textureShader = Shader::Create("assets/shaders/Texture.glsl");
		rendererData->textureShader->Bind();
		rendererData->textureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete rendererData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		rendererData->flatColorShader->Bind();
		rendererData->flatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		rendererData->textureShader->Bind();
		rendererData->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		// YEET YEET USELESS CALLLLL
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		rendererData->flatColorShader->Bind();
		rendererData->flatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			// * rotation
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->flatColorShader->SetMat4("u_Transform", transform);

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		rendererData->textureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			// * rotation
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->textureShader->SetMat4("u_Transform", transform);

		texture->Bind();

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
}

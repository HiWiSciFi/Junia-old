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
		Ref<Shader> shader;
		Ref<Texture2D> whiteTexture;
	};

	static Renderer2DStorage* rendererData;

	void Renderer2D::Init()
	{
		rendererData = new Renderer2DStorage();

		rendererData->vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 0.0f
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

		rendererData->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		rendererData->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		rendererData->shader = Shader::Create("assets/shaders/Texture.glsl");
		rendererData->shader->Bind();
		rendererData->shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete rendererData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		rendererData->shader->Bind();
		rendererData->shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		// YEET YEET USELESS CALLLLL
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		rendererData->shader->SetFloat4("u_Color", color);
		rendererData->whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			// * rotation
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->shader->SetMat4("u_Transform", transform);

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		rendererData->shader->SetFloat4("u_Color", tintColor);
		rendererData->shader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			// * rotation
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->shader->SetMat4("u_Transform", transform);

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		rendererData->shader->SetFloat4("u_Color", color);
		rendererData->whiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->shader->SetMat4("u_Transform", transform);

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		rendererData->shader->SetFloat4("u_Color", tintColor);
		rendererData->shader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->shader->SetMat4("u_Transform", transform);

		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
}

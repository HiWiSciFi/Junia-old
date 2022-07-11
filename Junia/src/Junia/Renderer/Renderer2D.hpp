#pragma once

#include <Junia/Renderer/OrthographicCamera.hpp>
#include <Junia/Renderer/Texture.hpp>

namespace Junia
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
			{ DrawQuad({ position.x, position.y, 0.0f }, size, color); }
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture)
			{ DrawQuad({ position.x, position.y, 0.0f }, size, texture); }
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);
	};
}

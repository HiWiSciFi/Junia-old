#pragma once

#include <Junia/Renderer/RenderCommand.hpp>
#include <Junia/Renderer/OrthographicCamera.hpp>
#include <Junia/Renderer/Shader.hpp>

namespace Junia
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};
}

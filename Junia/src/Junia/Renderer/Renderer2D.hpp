#pragma once

#include <Junia/Renderer/OrthographicCamera.hpp>

namespace Junia
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();


	};
}

#pragma once

#include <Junia/Renderer/OrthographicCamera.hpp>
#include <Junia/Core/Timestep.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/WindowEvents.hpp>

namespace Junia
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(const Timestep& deltaTime);
		[[nodiscard]] const OrthographicCamera& GetCamera() const { return camera; }

		void SetZoomLevel(const float level) { zoomLevel = level; }
		[[nodiscard]] float GetZoomLevel() const { return zoomLevel; }

	private:
		bool OnMouseScrolled(const MouseScrollEvent& e);
		bool OnWindowResized(const WindowResizeEvent& e);

		bool rotation = false;
		float cameraRotation = 0.0f;
		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
		float cameraRotationSpeed = 180.0f;
		float cameraMoveSpeed = 5.0f;

		float aspectRatio = 0.0f;
		float zoomLevel = 1.0f;
		OrthographicCamera camera = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}

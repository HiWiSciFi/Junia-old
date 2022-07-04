#include "OrthographicCameraController.hpp"
#include <Junia/Input.hpp>
#include <Junia/Log.hpp>

namespace Junia
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel), rotation(rotation)
	{
		MouseScrollEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(MouseScrollEvent, OnMouseScrolled));
		WindowResizeEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowResizeEvent, OnWindowResized));
	}

	void OrthographicCameraController::OnUpdate(Timestep deltaTime)
	{
		if (Input::IsKeyDown(JE_KEY_A))
			cameraPosition.x -= cameraMoveSpeed * deltaTime;
		else if (Input::IsKeyDown(JE_KEY_D))
			cameraPosition.x += cameraMoveSpeed * deltaTime;
		if (Input::IsKeyDown(JE_KEY_W))
			cameraPosition.y += cameraMoveSpeed * deltaTime;
		else if (Input::IsKeyDown(JE_KEY_S))
			cameraPosition.y -= cameraMoveSpeed * deltaTime;

		if (rotation)
		{
			if (Input::IsKeyDown(JE_KEY_Q))
				cameraRotation += cameraRotationSpeed * deltaTime;
			if (Input::IsKeyDown(JE_KEY_E))
				cameraRotation -= cameraRotationSpeed * deltaTime;
			camera.SetRotation(cameraRotation);
		}

		camera.SetPosition(cameraPosition);
		cameraMoveSpeed = zoomLevel;
	}

	bool OrthographicCameraController::OnMouseScrolled(const MouseScrollEvent& e)
	{
		zoomLevel -= e.GetYOffset() * 0.25f;
		zoomLevel = std::max(zoomLevel, .25f);
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(const WindowResizeEvent& e)
	{
		aspectRatio = static_cast<float>(e.GetWindowWidth()) / static_cast<float>(e.GetWindowHeight());
		camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}
}

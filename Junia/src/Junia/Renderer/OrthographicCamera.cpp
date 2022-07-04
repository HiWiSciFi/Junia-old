#include "OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Junia
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: viewMatrix(1.0f), projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		SetProjection(left, right, bottom, top);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); // l r b t zNear zFar
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}

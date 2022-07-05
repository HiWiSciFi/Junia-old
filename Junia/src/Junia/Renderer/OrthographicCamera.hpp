#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Junia
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		[[nodiscard]] const glm::vec3& GetPosition() const { return position; }
		[[nodiscard]] float GetRotation() const { return rotation; }

		void SetPosition(const glm::vec3& pos) { position = pos; RecalculateViewMatrix(); }
		void SetRotation(const float rot) { rotation = rot; RecalculateViewMatrix(); }

		[[nodiscard]] const glm::mat4& GetProjectionMatrix()     const { return     projectionMatrix; }
		[[nodiscard]] const glm::mat4& GetViewMatrix()           const { return           viewMatrix; }
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::ortho(1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f);
		glm::mat4 viewProjectionMatrix = glm::mat4(1.0f);

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
	};
}

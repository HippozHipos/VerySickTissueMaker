#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace vstm {

	class Camera {};

	class PerspectiveCamera : public Camera
	{
	public:
		//glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f
		PerspectiveCamera(float fovy, float aspect, float near, float far)
		{
			m_projection = glm::perspective(fovy, aspect, near, far);
			m_position = GetTranslation();
			m_rotation = GetRotation();
		};

	public:
		const glm::mat4& GetProjection()
		{
			return m_projection;
		}

		glm::mat4 GetTranslation()
		{
			return glm::translate(glm::mat4(1.0f), Position);
		}

		glm::mat4 GetRotation()
		{
			return  glm::rotate(glm::mat4(1.0f), Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		}

	public:
		glm::vec3 Position{ 0.0f, 0.0f, 0.0f, };
		glm::vec3 Rotation{ 0.0f, 0.0f, 0.0f };

	private:
		glm::mat4 m_position;
		glm::mat4 m_rotation;
		glm::mat4 m_projection;
	};

}
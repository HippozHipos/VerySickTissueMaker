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
		};

	public:
		const glm::mat4& GetProjectionMatrix()
		{
			return m_projection;
		}

		glm::mat4 GetViewMatrix()
		{
			m_right = glm::normalize(glm::cross(m_forward, m_world_up));
			return glm::lookAt(Position, Position + m_forward, 
				glm::normalize(glm::cross(m_right, m_forward)));
		}

		void SetWorldUp(const glm::vec3& up)
		{
			m_world_up = up;
		}

		void UpdateVectors()
		{
			m_forward.x = cos(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
			m_forward.y = sin(glm::radians(Rotation.y));
			m_forward.z = sin(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
			m_forward = glm::normalize(m_forward);

			if (Rotation.y > 89.0f)
				Rotation.y = 89.0f;
			if (Rotation.y < -89.0f)
				Rotation.y = -89.0f;
		}

		const glm::vec3& GetForwardVector()
		{
			return m_forward;
		}

	public:
		glm::vec3 Position{ 0.0f, 0.0f, -5.0f, };
		glm::vec3 Rotation{ 0.0f, 0.0f, 90.0f };

	private:
		glm::mat4 m_position;
		glm::mat4 m_rotation;
		glm::mat4 m_projection;


		glm::vec3 m_world_up{ 0.0f, 1.0f, 0.0f };
		glm::vec3 m_right{ 0.0f, 0.0f, 0.0f };

		glm::vec3 m_forward{ 0.0f, 0.0f, 0.0f };
	};

}
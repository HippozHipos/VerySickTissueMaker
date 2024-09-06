#include "Camera.h"

namespace vstmr {

	PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
	{
		m_projection = glm::perspective(fovy, aspect, near, far);
	}

	const glm::mat4& PerspectiveCamera::GetProjectionMatrix()
	{
		return m_projection;
	}

	glm::mat4 PerspectiveCamera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + m_forward, m_up);
	}

	void PerspectiveCamera::SetWorldUp(const glm::vec3& up)
	{
		m_world_up = up;
	}

	glm::vec3 PerspectiveCamera::Up()
	{
		return m_up;
	}

	glm::vec3 PerspectiveCamera::Right()
	{
		return m_right;
	}

	void PerspectiveCamera::UpdateVectors()
	{
		m_forward.x = cos(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
		m_forward.y = sin(glm::radians(Rotation.y));
		m_forward.z = sin(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}

	const glm::vec3& PerspectiveCamera::GetForwardVector()
	{
		return m_forward;
	}

	void PerspectiveCamera::ProcessKeyboardMovement(float deltaTime, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey)
	{
		float velocity = m_movement_speed * deltaTime;
		if (forwardKey)
			Position += m_forward * velocity;
		if (backKey)
			Position -= m_forward * velocity;
		if (rightKey)
			Position += m_right * velocity;
		if (leftKey)
			Position -= m_right * velocity;
		if (upKey)
			Position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		if (downKey)
			Position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	}

	void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch)
	{
		xoffset *= m_mouse_sensitivity;
		yoffset *= m_mouse_sensitivity;

		Rotation.z += xoffset;
		Rotation.y += yoffset;

		if (constrain_pitch)
		{
			if (Rotation.y > 89.0f)
				Rotation.y = 89.0f;
			if (Rotation.y < -89.0f)
				Rotation.y = -89.0f;
		}

		UpdateVectors();
	}

	void PerspectiveCamera::ProcessMouseScroll(float yoffset)
	{
		m_zoom -= (float)yoffset;
		if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		if (m_zoom > 45.0f)
			m_zoom = 45.0f;
	}
	

}
#include "Camera.h"

namespace vstmr {

	Camera::Camera(float fovy, float aspect, float near, float far)
	{
		RecalculateProjectionMatrix(fovy, aspect, near, far);
	}

	void Camera::RecalculateProjectionMatrix(float fovy, float aspect, float near, float far)
	{
		m_projection = glm::perspective(fovy, aspect, near, far);
	}

	const glm::mat4& Camera::GetProjectionMatrix()
	{
		return m_projection;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(Position, Position + m_forward, m_up);
	}

	void Camera::SetWorldUp(const glm::vec3& up)
	{
		m_world_up = up;
	}

	glm::vec3 Camera::Up()
	{
		return m_up;
	}

	glm::vec3 Camera::Right()
	{
		return m_right;
	}

	void Camera::UpdateVectors()
	{
		m_forward.x = cos(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
		m_forward.y = sin(glm::radians(Rotation.y));
		m_forward.z = sin(glm::radians(Rotation.z)) * cos(glm::radians(Rotation.y));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}

	const glm::vec3& Camera::GetForwardVector()
	{
		return m_forward;
	}

	void Camera::ProcessKeyboardMovement(float deltaTime, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey)
	{
		//float velocity = m_movement_speed * deltaTime;
		float velocity = MovementSpeed * deltaTime;
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

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch)
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

	void Camera::ProcessMouseScroll(float yoffset)
	{
		m_zoom -= (float)yoffset;
		if (m_zoom < 1.0f)
			m_zoom = 1.0f;
		if (m_zoom > 45.0f)
			m_zoom = 45.0f;
	}
	

}
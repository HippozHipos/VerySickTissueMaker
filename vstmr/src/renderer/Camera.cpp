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
		return glm::lookAt(position, position + m_forward, m_up);
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

	void Camera::Update()
	{
		m_forward.x = cos(glm::radians(rotation.z)) * cos(glm::radians(rotation.y));
		m_forward.y = sin(glm::radians(rotation.y));
		m_forward.z = sin(glm::radians(rotation.z)) * cos(glm::radians(rotation.y));
		m_forward = glm::normalize(m_forward);

		m_right = glm::normalize(glm::cross(m_forward, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}

	const glm::vec3& Camera::Forward()
	{
		return m_forward;
	}	

}
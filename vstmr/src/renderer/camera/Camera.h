#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>

namespace vstmr {

	class Camera {};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(float fovy, float aspect, float near, float far);

	public:
		const glm::mat4& GetProjectionMatrix();

		glm::mat4 GetViewMatrix();

		void SetWorldUp(const glm::vec3& up);

		void UpdateVectors();
		
		const glm::vec3& GetForwardVector();

		void ProcessKeyboardMovement(float deltaTime, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey);

		void ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch = true);

		void ProcessMouseScroll(float yoffset);

	public:
		glm::vec3 Position{ 0.0f, 0.0f, -5.0f, };
		glm::vec3 Rotation{ 0.0f, 0.0f, 90.0f };

	private:
		std::function<void(Camera& camera)> m_movement_callback;

		glm::mat4 m_position;
		glm::mat4 m_rotation;
		glm::mat4 m_projection;

		// Camera settings
		float m_movement_speed = 2.5f;
		float m_mouse_sensitivity = 0.1f;
		float m_zoom = 45.0f;

		glm::vec3 m_world_up{ 0.0f, 1.0f, 0.0f };
		glm::vec3 m_right{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_forward{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_up{ 0.0f, 0.0f, 0.0f };
	};

}
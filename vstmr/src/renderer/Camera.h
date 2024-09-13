#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>

#include "ECS/SceneObject.h"

namespace be {

	class Camera : public SceneObject
	{
	public:
		Camera(float fovy, float aspect, float near, float far);

	public:
		const glm::mat4& GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
		void SetWorldUp(const glm::vec3& up);
		void Update();
		const glm::vec3& Forward();
		void RecalculateProjectionMatrix(float fovy, float aspect, float near, float far);
		glm::vec3 Right();
		glm::vec3 Up();

	public:
		glm::vec3 position{ 0.0f, 0.0f, -5.0f, };
		glm::vec3 rotation{ 0.0f, 0.0f, 90.0f };
		float movement_speed = 5;
		float mouse_sensitivity = 0.1f;
		std::string target_viewport = "Main Platform Window";
		bool active = true;

	private:
		glm::mat4 m_position;
		glm::mat4 m_rotation;
		glm::mat4 m_projection;
	
		glm::vec3 m_world_up{ 0.0f, 1.0f, 0.0f };
		glm::vec3 m_right{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_forward{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_up{ 0.0f, 0.0f, 0.0f };
	};

}
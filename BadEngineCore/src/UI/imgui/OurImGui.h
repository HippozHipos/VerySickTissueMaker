#pragma once
#include "pch.h"
#include <imgui.h>

#include "UI/Imgui/imgui_impl_glfw.h"
#include "UI/Imgui/imgui_impl_opengl3.h"
#include "Renderer/Renderer.h"

class GLFWwindow;
namespace be {

	class OurImGui
	{
	public:
		void Start(GLFWwindow* window, int config_flag);
		void Render(GLFWwindow* window, Renderer& renderer, int config_flag);
		void Destroy();
	};

}
#pragma once

#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "renderer/Renderer.h"

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
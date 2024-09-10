#pragma once

#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

class GLFWwindow;
namespace vstmr {

	class OurImGui
	{
	public:
		void Start(GLFWwindow* window);
		void Render(GLFWwindow* window);
		void RenderMainDockspace();

		void Destroy();
	};

}
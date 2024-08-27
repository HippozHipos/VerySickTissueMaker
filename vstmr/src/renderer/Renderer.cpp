#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"
#include "Viewport.h"
#include "vstmr/LayerStack.h"
#include "vstmr/Layer.h"

namespace vstmr {


	Renderer::Renderer(Window* window) :
		m_window{ window }
	{
		m_shaders = std::make_unique<Shaders>();
		m_shaders->Use();
		m_vertex_array.Bind();

		//m_shaders->SetInt("tex0", 0);
	
		// Enable depth testing and backface culling
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_SCISSOR_TEST);

		CheckOpenGLError();
	}

	

	void Renderer::Render()
	{
		m_vertex_array.Bind();

		LayerStack* stack = m_window->GetLayerStack();
		for (size_t i = 0; i < stack->Size(); i++)
		{
			Layer* layer = stack->GetLayer(i);
			for (size_t j = 0; j < layer->NumViewports(i); j++)
			{
				m_shaders->SetMat4f("projection", layer->GetCamera().GetProjectionMatrix());
				m_shaders->SetMat4f("view", layer->GetCamera().GetViewMatrix());
				layer->GetCamera().UpdateVectors();

				Viewport* viewport = layer->GetViewport(j);
				viewport->UpdateViewport();

				//NOTE:REMOVE LATER
				glClearColor(viewport->r, viewport->g, viewport->b, viewport->a);
				// Clear both color and depth buffer
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glDrawElements(GL_TRIANGLES, 26700, GL_UNSIGNED_INT, nullptr);
			}
		}

		CheckOpenGLError();
	}

	void Renderer::SetLayout()
	{
		m_vertex_array.SetupLayout<float>(3);  // Position (x, y, z)
		//m_vertex_array.SetupLayout<float>(4);  // Color (r, g, b, a)
		//m_vertex_array.SetupLayout<float>(2);  // Texture coordinates (u, v)

		m_vertex_array.AddLayout();

		CheckOpenGLError();
	}
}
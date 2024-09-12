#include <imgui.h>
#include <imgui_internal.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MeshRendererSystem.h"

#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"
#include "diagnostics/OpenglError.h"
#include "renderer/Camera.h"
#include "renderer/Renderer.h"
#include "renderer/Material.h"
#include "renderer/Transform.h"
#include "renderer/PointLight.h"

#include "renderer/Graphics.h"

namespace vstmr {

	MeshRendererSystem::MeshRendererSystem(std::unordered_map<std::string, VstmrImGuiViewport>& viewportMap, 
		MainPlatformWindowRenderer& mainWinRenderer) :
		m_viewport_map{ viewportMap }, m_main_window_renderer{ mainWinRenderer }
	{
	}

	void MeshRendererSystem::Render()
	{
		auto cameras = ECS::registry.view<Camera>();
		for (auto& entityOuter : cameras)
		{
			Camera& camera = cameras.get<Camera>(entityOuter);
			if (camera.active)
			{
				auto it = m_viewport_map.find(camera.target_viewport.c_str());
				bool isMainPlatformWindow = camera.target_viewport == "Main Platform Window";
				if (it == m_viewport_map.end() && !isMainPlatformWindow)
				{
					VSTM_CON_LOGWARN("Trying to render to viewport that doesn't exist: {}", camera.target_viewport.c_str());
					return;
				}
				if (isMainPlatformWindow)
				{
					FrameBuffer::UnBind();
					/*Window& window = ECS::registry.view<Window>().get<Window>((entt::entity)0);
					if (window.GetWidth() != m_main_window_renderer.GetWidth() || window.GetHeight() != m_main_window_renderer.GetHeight())
					{
						m_main_window_renderer.ResizeContext(window.GetWidth(), window.GetHeight());
					}
					m_main_window_renderer.BindFrameBuffer();*/
				}
				else
				{
					it->second.BindFrameBuffer();
					Graphics::UpdateViewport(0, 0, it->second.GetWidth(), it->second.GetHeight());
				}
				Graphics::ClearBuffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				auto meshRenderers = ECS::registry.view<MeshRenderer>();
				for (auto& entityInner : meshRenderers)
				{
					MeshRenderer& renderer = meshRenderers.get<MeshRenderer>(entityInner);
					Transform& transform = renderer.GetParent<Transform>();

					ProcessLighting(renderer);
					RenderMesh(camera, renderer, transform);
				}
/*				if (isMainPlatformWindow)
				{
					m_main_window_renderer.Render();
				}	*/				
			}
		}
		VertexArray::UnBind();
		FrameBuffer::UnBind();
	}

	void MeshRendererSystem::ProcessLighting(MeshRenderer& renderer)
	{
		renderer.material.shaders.Use();

		auto view = ECS::registry.view<PointLight>();
		for (auto entity : view)
		{
			PointLight& light = view.get<PointLight>(entity);
			renderer.material.shaders.Use();
			renderer.material.shaders.SetVec3f("lightColor", light.color);
			renderer.material.shaders.SetVec3f("lightPos", light.GetParent<Transform>().position);
		}
	}

	void MeshRendererSystem::RenderMesh(Camera& camera, MeshRenderer& renderer, Transform& transform)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, transform.scale);

		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(glm::mat4(1.0f), transform.position) * model;

		renderer.material.shaders.SetMat4f("model", model);

		Graphics::SetPolygonDrawMode(renderer.draw_mode);
		
		int i = 0;
		for (MeshComponent& mesh : renderer.meshes)
		{
			mesh.vertex_array.Bind();
			mesh.index_buffer.Bind();
			mesh.vertex_buffer.Bind();

			renderer.material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
			renderer.material.shaders.SetMat4f("view", camera.GetViewMatrix());
			renderer.material.shaders.SetVec3f("materialColor", renderer.material.color);

			Graphics::SetActiveTextureSlot(GL_TEXTURE0);
			renderer.material.textures[i++].Bind();

			Graphics::DrawIndexedTraingles(mesh.index_data.size());
		}
	}
}
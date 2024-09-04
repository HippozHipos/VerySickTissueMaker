#include <glad/glad.h>

#include "MeshRendererProcessor.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"
#include "diagnostics/OpenglError.h"
#include "renderer/camera/Camera.h"
#include "renderer/Renderer.h"
#include "renderer/Material.h"

#include "ECS/ECS.h"

namespace vstmr {


	void MeshRendererProcessor::Render()
	{
		auto view = ECS::registry.view<MeshRenderer>();

		for (auto entity : view)
		{
			MeshRenderer& renderer = view.get<MeshRenderer>(entity);
			MeshComponent& mesh = renderer.GetComponent<MeshComponent>();
			Material& material = renderer.GetComponent<Material>();

			mesh.vertex_array.Bind();
			mesh.index_buffer.Bind();

			//quick dirty hack for now since i have put camera in renderer
			auto rendererView = ECS::registry.view<Renderer>();
			PerspectiveCamera camera;
			for (auto entity : rendererView)
			{
				camera = rendererView.get<Renderer>(entity).camera;
			}
			
			material.shaders.Use();
			material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
			material.shaders.SetMat4f("view", camera.GetViewMatrix());

			glDrawElements(GL_TRIANGLES, mesh.index_data.size(), GL_UNSIGNED_INT, nullptr);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		CheckOpenGLError();
	}

}
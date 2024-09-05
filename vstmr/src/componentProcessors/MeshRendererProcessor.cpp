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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto entity : view)
		{
			MeshRenderer& renderer = view.get<MeshRenderer>(entity);
			vstmr::VectorComponent<vstmr::MeshComponent>& meshes = renderer.GetComponent<vstmr::VectorComponent<vstmr::MeshComponent>>();
			Material& material = renderer.GetComponent<Material>();

			//quick dirty hack for now since i have put camera in renderer
			auto rendererView = ECS::registry.view<Renderer>();
			PerspectiveCamera camera;
			for (auto entity : rendererView)
			{
				camera = rendererView.get<Renderer>(entity).camera;
			}

			for (MeshComponent& mesh : meshes.vector)
			{
				mesh.vertex_array.Bind();
				mesh.index_buffer.Bind();
				mesh.vertex_buffer.Bind();

				mesh.vertex_buffer.BufferSubData((void*)mesh.vertex_data.data(), mesh.VertexBufferSize(), 0);
				mesh.index_buffer.BufferData((void*)mesh.index_data.data(), mesh.IndexBufferSize(), 0);

				material.shaders.Use();
				material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
				material.shaders.SetMat4f("view", camera.GetViewMatrix());
				material.shaders.SetVec3f("materialColor", material.color);

				static float angle = 0.0f;
				glm::mat4 model = glm::mat4(1.0f); 
				model = glm::translate(model, { 0.0f, 0.0f, 0.0f });
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				material.shaders.SetMat4f("model", model);

				glDrawElements(GL_TRIANGLES, mesh.index_data.size(), GL_UNSIGNED_INT, nullptr);
			}

		}
		CheckOpenGLError();
	}

}
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MeshRendererProcessor.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"
#include "diagnostics/OpenglError.h"
#include "renderer/camera/Camera.h"
#include "renderer/Renderer.h"
#include "renderer/Material.h"
#include "renderer/Transform.h"
#include "renderer/PointLight.h"

namespace vstmr {

	void MeshRendererProcessor::Render()
	{
		//REMINDER: FIXME; quick dirty hack for now since i have put camera in application container
		Camera& camera = ECS::registry.view<Camera>().get<Camera>((entt::entity)0);	

		auto view = ECS::registry.view<MeshRenderer>();
		for (auto entity : view)
		{
			MeshRenderer& renderer = view.get<MeshRenderer>(entity);
			Transform& transform = renderer.GetParent<Transform>();
			VectorComponent<MeshComponent>& meshes = renderer.Get<VectorComponent<MeshComponent>>();
			Material& material = renderer.Get<Material>();

			ProcessLighting(renderer, material);
			RenderMesh(camera, renderer, transform, meshes, material);
		}
		CheckOpenGLError();
	}

	void MeshRendererProcessor::ProcessLighting(MeshRenderer& renderer,  Material& material)
	{
		material.shaders.Use();

		auto view = ECS::registry.view<PointLight>();
		for (auto entity : view)
		{
			PointLight& light = view.get<PointLight>(entity);
			material.shaders.Use();
			material.shaders.SetVec3f("lightColor", light.color);
			material.shaders.SetVec3f("lightPos", light.GetParent<Transform>().position);
		}
	}

	void MeshRendererProcessor::RenderMesh(
		Camera& camera, MeshRenderer& renderer, 
		Transform& transform, VectorComponent<MeshComponent>& meshes, 
		Material& material)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, transform.scale);

		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(glm::mat4(1.0f), transform.position) * model;

		material.shaders.SetMat4f("model", model);

		if (renderer.wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		for (MeshComponent& mesh : meshes.vector)
		{
			mesh.vertex_array.Bind();
			mesh.index_buffer.Bind();
			mesh.vertex_buffer.Bind();

			/*mesh.vertex_buffer.BufferSubData((void*)mesh.vertex_data.data(), mesh.VertexBufferSize(), 0);
			mesh.index_buffer.BufferData((void*)mesh.index_data.data(), mesh.IndexBufferSize(), 0);*/

			material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
			material.shaders.SetMat4f("view", camera.GetViewMatrix());
			material.shaders.SetVec3f("materialColor", material.color);

			

			glDrawElements(GL_TRIANGLES, mesh.index_data.size(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
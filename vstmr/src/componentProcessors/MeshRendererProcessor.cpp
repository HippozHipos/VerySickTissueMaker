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

	//IMPORTANT NOTE: For now, we get mesh renderer from transform so this code will break if a container has transform 
	//but not mesh renderer. We need a more powerful system, maybe something like each container and 
	//component not only stores the entity it is/belongs to but also all the parent and children entities.
	//void MeshRendererProcessor::Render()
	//{
	//	auto view = ECS::registry.view<Transform>();

	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	for (auto entity : view)
	//	{
	//		Transform& transform = view.get<Transform>(entity);
	//		MeshRenderer& renderer = transform.GetComponent<MeshRenderer>();
	//		vstmr::VectorComponent<vstmr::MeshComponent>& meshes = renderer.GetComponent<vstmr::VectorComponent<vstmr::MeshComponent>>();
	//		Material& material = renderer.GetComponent<Material>();

	//		//quick dirty hack for now since i have put camera in renderer
	//		auto rendererView = ECS::registry.view<Renderer>();
	//		PerspectiveCamera camera;
	//		for (auto entity : rendererView)
	//		{
	//			camera = rendererView.get<Renderer>(entity).camera;
	//		}

	//		glm::mat4 model = glm::mat4(1.0f);

	//		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//		model = glm::translate(glm::mat4(1.0f), transform.position) * model;

	//		Shaders& shaders = transform.GetComponent<MeshRenderer>().GetComponent<Material>().shaders;
	//		shaders.Use();
	//		shaders.SetMat4f("model", model);

	//		for (MeshComponent& mesh : meshes.vector)
	//		{
	//			mesh.vertex_array.Bind();
	//			mesh.index_buffer.Bind();
	//			mesh.vertex_buffer.Bind();

	//			mesh.vertex_buffer.BufferSubData((void*)mesh.vertex_data.data(), mesh.VertexBufferSize(), 0);
	//			mesh.index_buffer.BufferData((void*)mesh.index_data.data(), mesh.IndexBufferSize(), 0);

	//			material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
	//			material.shaders.SetMat4f("view", camera.GetViewMatrix());
	//			material.shaders.SetVec3f("materialColor", material.color);

	//			glDrawElements(GL_TRIANGLES, mesh.index_data.size(), GL_UNSIGNED_INT, nullptr);
	//		}

	//	}
	//	CheckOpenGLError();
	//}

	//void MeshRendererProcessor::Render()
	//{
	//	auto view = ECS::registry.view<Transform>();

	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	for (auto entity : view)
	//	{
	//		Transform& transform = view.get<Transform>(entity);
	//		MeshRenderer& renderer = transform.Get<MeshRenderer>();
	//		vstmr::VectorComponent<vstmr::MeshComponent>& meshes = renderer.Get<vstmr::VectorComponent<vstmr::MeshComponent>>();
	//		Material& material = renderer.Get<Material>();

	//		//quick dirty hack for now since i have put camera in renderer
	//		auto rendererView = ECS::registry.view<Renderer>();
	//		PerspectiveCamera camera;
	//		for (auto entity : rendererView)
	//		{
	//			camera = rendererView.get<Renderer>(entity).camera;
	//		}

	//		glm::mat4 model = glm::mat4(1.0f);

	//		model = glm::scale(model, transform.scale);

	//		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//		model = glm::translate(glm::mat4(1.0f), transform.position) * model;

	//		Shaders& shaders = transform.Get<MeshRenderer>().Get<Material>().shaders;
	//		shaders.Use();
	//		shaders.SetMat4f("model", model);

	//		for (MeshComponent& mesh : meshes.vector)
	//		{
	//			mesh.vertex_array.Bind();
	//			mesh.index_buffer.Bind();
	//			mesh.vertex_buffer.Bind();

	//			mesh.vertex_buffer.BufferSubData((void*)mesh.vertex_data.data(), mesh.VertexBufferSize(), 0);
	//			mesh.index_buffer.BufferData((void*)mesh.index_data.data(), mesh.IndexBufferSize(), 0);

	//			{
	//				//THIS IS THE LIGHT BIT
	//				auto view = ECS::registry.view<PointLight>();

	//				for (auto entity : view)
	//				{
	//					PointLight& light = view.get<PointLight>(entity);
	//					MeshRenderer& renderer = light.Get<MeshRenderer>();

	//					Shaders& shaders = renderer.Get<Material>().shaders;
	//					shaders.Use();
	//					shaders.SetVec3f("lightColor", light.color);
	//				}
	//			}

	//			material.shaders.SetMat4f("projection", camera.GetProjectionMatrix());
	//			material.shaders.SetMat4f("view", camera.GetViewMatrix());
	//			material.shaders.SetVec3f("materialColor", material.color);

	//			glDrawElements(GL_TRIANGLES, mesh.index_data.size(), GL_UNSIGNED_INT, nullptr);
	//		}

	//	}
	//	CheckOpenGLError();
	//}

	void MeshRendererProcessor::Render()
	{
		//REMINDER: FIXME; quick dirty hack for now since i have put camera in renderer
		auto rendererView = ECS::registry.view<Renderer>();
		PerspectiveCamera camera;
		for (auto entity : rendererView)
		{
			camera = rendererView.get<Renderer>(entity).camera;
		}

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
		PerspectiveCamera& camera, MeshRenderer& renderer, 
		Transform& transform, VectorComponent<MeshComponent>& meshes, 
		Material& material)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(glm::mat4(1.0f), transform.position) * model;

		material.shaders.SetMat4f("model", model);

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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Application.h"
#include "diagnostics/Logger.h"
#include "diagnostics/Error.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"
#include "diagnostics/OpenglError.h"
#include "timer/timer.h"

namespace rend {

	// Vertex data for a cube
	std::vector<float> vertices;
	// Indices for drawing the cube using element array
	std::vector<int> indices;

	void load()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile("../../../assets/models/Ukulele.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VSTM_CON_LOGERROR("ERROR::ASSIMP::{}", importer.GetErrorString());
			return;
		}

		//aiNode* root = scene->mRootNode;
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			for (int j = 0; j < mesh->mNumVertices; j++)
			{
				vertices.push_back(mesh->mVertices[j].x);
				vertices.push_back(mesh->mVertices[j].y);
				vertices.push_back(mesh->mVertices[j].z);
			}
			for (int j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (int k = 0; k < face.mNumIndices; k++)
				{
					indices.push_back(face.mIndices[k]);
				}
			}

		}
	}

	void setup(vstm::Renderer& renderer)
	{
		load();

		vstm::VertexBuffer vertexBuffer;
		vstm::IndexBuffer indexBuffer;

		int sizefloat = vertices.size() * sizeof(float);
		int sizeint = indices.size() * sizeof(int);

		vertexBuffer.Bind();
		vertexBuffer.BufferData(sizefloat);
		vertexBuffer.BufferSubData(vertices.data(), sizefloat, 0);
		
		indexBuffer.Bind();
		indexBuffer.BufferData(sizeint);
		indexBuffer.BufferSubData(indices.data(), sizeint, 0);

		renderer.SetLayout();
	}
}

namespace vstm {

	Application::Application() :
		m_window{ 600, 600, "Very sick tissue maker" }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");

		// This removes the visibility of the cursor
		//glfwSetInputMode(m_window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set initial cursor position to the center of the screen
		m_lastX = m_window.GetWidth() / 2.0;
		m_lastY = m_window.GetHeight() / 2.0;
		m_window.SetCursorPos(m_lastX, m_lastY);

		Texture cat = m_texture_manager.Load("cat", "../../../assets/images/cover.thumb256.png");
		Texture cat2 = m_texture_manager.HardCopy("cat2", cat);
		glActiveTexture(GL_TEXTURE0);
		cat2.Bind();
		cat2.SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		m_texture_manager.Get("cat2").SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		cat2.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		cat2.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Application::Run()
	{
		ErrorHandler::Handle();
		HandleErrorActions();

		rend::setup(m_renderer);
		
		// note that this is allowed, the call to glVertexAttribPointer registered
		// VBO as the vertex attribute's bound vertex buffer object so afterwards 
		// we can safely unbind
		vstm::VertexBuffer::UnBind();

		Timer timer{};

		while (!m_window.IsClosed() && m_running)
		{
			double deltaTime = timer.getDeltaTime();

			m_window.Fill(0.2f, 0.3f, 0.3f, 1.0f);
			
			ProcessInput(deltaTime);
			m_renderer.Render();
			
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
	}

	void Application::ProcessInput(double deltaTime)
	{
		// Keyboard input
		m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 
			m_window.KeyHeld(GLFW_KEY_W), m_window.KeyHeld(GLFW_KEY_S),
			m_window.KeyHeld(GLFW_KEY_A), m_window.KeyHeld(GLFW_KEY_D),
			m_window.KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window.KeyHeld(GLFW_KEY_SPACE));

		// Mouse input
		float xoffset = m_window.GetMouseX()- m_lastX;
		float yoffset = m_lastY - m_window.GetMouseY(); // Reversed since y-coordinates go from bottom to top

		m_lastX = m_window.GetMouseX();
		m_lastY = m_window.GetMouseY();

		m_renderer.GetCamera().ProcessMouseMovement(xoffset, yoffset);
		// Reset the cursor to the centre of the screen
		m_window.CenterCursorPos(m_lastX, m_lastY);
	}

	void Application::HandleErrorActions()
	{
		for (size_t i = 0; i < ErrorHandler::NumActions(); i++)
		{
			switch (ErrorHandler::GetAction(i))
			{
				case ErrorHandler::TerminateApplication: m_running = false;

			}
		}
	}

}

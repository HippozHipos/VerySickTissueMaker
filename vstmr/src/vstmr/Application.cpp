#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "Application.h"
#include "diagnostics/Logger.h"
#include "diagnostics/Error.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"
#include "diagnostics/OpenglError.h"
#include "timer/timer.h"

#include "renderer/BufferSetStore.h"

namespace rend {

	std::vector<float> vertices;
	std::vector<int> indices;

	void load()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile("../../../../vstmr/assets/models/Ukulele.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

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

	vstmr::BufferSetStore buffersetStore;

	void setup()
	{
		load();

		buffersetStore.SetBufferLayouts(vstmr::BufferSetStore::VERTEX, vstmr::BufferSetStore::EMPTY, 
									    vstmr::BufferSetStore::EMPTY, vstmr::BufferSetStore::EMPTY);

		buffersetStore.SetBufferLayoutTypes(GL_FLOAT, vstmr::BufferSetStore::EMPTY,
									  vstmr::BufferSetStore::EMPTY, vstmr::BufferSetStore::EMPTY);

		buffersetStore.SetVertexData((void*)vertices.data(), vertices.size() * sizeof(float));
		buffersetStore.SetIndexData((void*)indices.data(), indices.size() * sizeof(int));

		buffersetStore.AddBufferSet();
	}
}

namespace vstmr {

	Application::Application() :
		m_window{ 600, 600, "Very sick tissue maker" },
		m_renderer{ &m_window }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");

		//Texture cat = m_texture_manager.Load("cat", "../../../../vstmr/assets/images/cover.thumb256.png");
		//Texture cat2 = m_texture_manager.HardCopy("cat2", cat);
		////glActiveTexture(GL_TEXTURE0);
		//cat2.Bind();
		//cat2.SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		//m_texture_manager.Get("cat2").SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		//cat2.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//cat2.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Application::Run()
	{
		ImGuiSetup();

		ErrorHandler::Handle();
		HandleErrorActions();

		Start();
		rend::setup();

		while (!m_window.IsClosed())// && m_running)
		{
			float deltaTime = m_timer.getDeltaTime();
			Update(deltaTime);

			m_window.GetViewport().ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			m_renderer.Render();
			ImGuiDraw();

			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
		End();
	}

	void Application::ImGuiSetup()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window.GetGLFWWindow(), true);
#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void Application::ImGuiDraw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui(io);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(m_window.GetGLFWWindow());
		}
	}

	//default overrides
	void Application::Start() {}
	void Application::Update(float deltaTime) {}
	void Application::ImGui(ImGuiIO& io) {}
	void Application::End() {}

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

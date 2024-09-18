#pragma once
#include "pch.h"
#include <imgui.h>

#include "Renderer/buffers/FrameBuffer.h"

namespace be {

	class BEImGuiViewport
	{
	public:
		BEImGuiViewport(const char* name);

	public:
		void BindFrameBuffer();
		/*! 
		* \brief Gives a frame buffer texture to draw to imgui for the window that the framebuffer belong to.
		* The texture will already be drawn on by MeshRendererSystem::Render when this function is called.
		*/
		void Render();
		int GetWidth();
		int GetHeight();
		ImGuiWindowFlags GetFlags();
		void AddFlags(ImGuiWindowFlags flags);
		void SetFlags(ImGuiWindowFlags flags);

	private:
		const char* m_name;
		ImGuiWindowFlags m_flags = 0;
		FrameBuffer m_frame_buffer;
	};

}
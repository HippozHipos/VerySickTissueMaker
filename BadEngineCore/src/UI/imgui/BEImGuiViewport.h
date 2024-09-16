#pragma once
#include "pch.h"
#include <imgui.h>

#include "Renderer/buffers/FrameBuffer.h"

namespace be {

	class VstmrImGuiViewport
	{
	public:
		VstmrImGuiViewport(const char* name);

	public:
		void BindFrameBuffer();
		void Render();
		int GetWidth();
		int GetHeight();

	private:
		const char* m_name;
		ImGuiWindowFlags m_flags = 0;
		FrameBuffer m_frame_buffer;
	};

}
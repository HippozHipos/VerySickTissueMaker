#include "VstmrImGuiViewport.h"
#include "renderer/Graphics.h"

namespace vstmr {

	VstmrImGuiViewport::VstmrImGuiViewport(const char* name) :
		m_name{ name }
	{
		m_flags |= ImGuiWindowFlags_NoScrollbar;
		m_frame_buffer.Init();
		m_frame_buffer.CreateAttachments(1, 1);//just so we dont go first frame without valid frame buffer
	}

	void VstmrImGuiViewport::BindFrameBuffer()
	{
		m_frame_buffer.Bind();
	}

	int VstmrImGuiViewport::GetWidth()
	{
		return m_frame_buffer.GetWidth();
	}

	int VstmrImGuiViewport::GetHeight()
	{
		return m_frame_buffer.GetHeight();
	}

	void VstmrImGuiViewport::Render()
	{
		ImGui::Begin(m_name, nullptr, m_flags);
		if (ImGui::GetWindowWidth() != m_frame_buffer.GetWidth() || ImGui::GetWindowHeight() != m_frame_buffer.GetHeight())
		{
			m_frame_buffer.CreateAttachments(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());	
		}
		ImTextureID texture = (ImTextureID)m_frame_buffer.GetTexture().Id();
		ImGui::Image(texture, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}
}

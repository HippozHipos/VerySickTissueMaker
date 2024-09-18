#include "BEImGuiViewport.h"
#include "Renderer/Graphics.h"

namespace be {

	BEImGuiViewport::BEImGuiViewport(const char* name) :
		m_name{ name }
	{
		m_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		m_frame_buffer.Init();
		m_frame_buffer.CreateAttachments(1, 1);//just so we dont go first frame without valid frame buffer
	}

	void BEImGuiViewport::BindFrameBuffer()
	{
		m_frame_buffer.Bind();
	}

	int BEImGuiViewport::GetWidth()
	{
		return m_frame_buffer.GetWidth();
	}

	int BEImGuiViewport::GetHeight()
	{
		return m_frame_buffer.GetHeight();
	}

	int BEImGuiViewport::GetFlags()
	{
		return m_flags;
	}

	void BEImGuiViewport::AddFlags(ImGuiWindowFlags flags)
	{
		m_flags |= flags;
	}

	void BEImGuiViewport::SetFlags(ImGuiWindowFlags flags)
	{
		m_flags = flags;
	}

	void BEImGuiViewport::Render()
	{
		ImGui::Begin(m_name, nullptr, m_flags);
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != m_frame_buffer.GetWidth() || size.y != m_frame_buffer.GetHeight())
		{
			m_frame_buffer.CreateAttachments(size.x, size.y);	
		}
		ImTextureID texture = (ImTextureID)m_frame_buffer.GetTexture().Id();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::Image(texture, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}
}

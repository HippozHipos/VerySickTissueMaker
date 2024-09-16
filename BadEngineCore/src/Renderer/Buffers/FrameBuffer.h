#pragma once

#include "Renderer/Texture.h"
#include "RenderBuffer.h"

namespace be {

	class FrameBuffer
	{
	public:
		FrameBuffer() = default;
		~FrameBuffer();

	public:
		void Init();
		void Bind();
		void BindRenderBuffer();
		static void BindDefault();
		static void UnBind();
		void Destroy();
		bool HasTextureAttachment();
		void CreateAttachments(int width, int height);
		Texture GetTexture();
		int GetWidth();
		int GetHeight();

	private:
		void CreateTextureAttachment(int width, int height);
		void CreateRenderBufferAttachment(int width, int height);

	private:
		Texture m_texture_attachment{};
		RenderBuffer m_render_buffer{};

		bool m_has_render_buffer_attachment = false;

		int m_width = 0;
		int m_height = 0;
		unsigned int m_buffer_id{};
	};

}
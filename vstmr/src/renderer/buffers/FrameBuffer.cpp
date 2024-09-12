#include <glad/glad.h>

#include "FrameBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	FrameBuffer::~FrameBuffer()
	{
		if (m_has_render_buffer_attachment)
		{
			m_render_buffer.Destroy();
		}
	}

	void FrameBuffer::Init()
	{
		glGenFramebuffers(1, &m_buffer_id);
		m_render_buffer.Init();
		CheckOpenGLError();
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_buffer_id);
	}

	void FrameBuffer::BindRenderBuffer()
	{
		m_render_buffer.Bind();
	}

	int FrameBuffer::GetWidth()
	{
		return m_width;
	}

	int FrameBuffer::GetHeight()
	{
		return m_height;
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		CheckOpenGLError();
	}

	void FrameBuffer::Destroy()
	{
		glDeleteFramebuffers(1, &m_buffer_id);
		CheckOpenGLError();
	}

	Texture FrameBuffer::GetTexture()
	{
		return m_texture_attachment;
	}

	void FrameBuffer::CreateAttachments(int width, int height)
	{
		m_width = width;
		m_height = height;
		CreateTextureAttachment(width, height);
		CreateRenderBufferAttachment(width, height);
	}

	void FrameBuffer::CreateTextureAttachment(int width, int height)
	{
		Texture texture{ nullptr, width, height, 4, false };
		texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Bind();
		texture.AttachToFrameBuffer();
		UnBind();
		m_texture_attachment = texture;
	}

	void FrameBuffer::CreateRenderBufferAttachment(int width, int height)
	{
		if (m_has_render_buffer_attachment)
		{
			m_render_buffer.Destroy();
			m_render_buffer.Init();
		}
		m_render_buffer.Bind();
		m_render_buffer.MakeStorage(width, height);
		Bind();
		m_render_buffer.AttachToFrameBuffer();
		UnBind();
		RenderBuffer::UnBind();
		m_has_render_buffer_attachment = true;
	}

}
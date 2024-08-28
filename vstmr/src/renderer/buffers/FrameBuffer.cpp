#include <glad/glad.h>

#include "FrameBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &m_buffer_id);
		CheckOpenGLError();
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_buffer_id);
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

	bool FrameBuffer::HasTextureAttachment()
	{
		return m_has_texture_attachment;
	}

	bool FrameBuffer::HasRenderBufferAttachment()
	{
		return m_has_render_buffer_attachment;
	}

	Texture FrameBuffer::CreateTextureAttachment(int width, int height)
	{
		m_has_texture_attachment = true;
		Texture texture{ nullptr, width, height, false };
		texture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Bind();
		texture.AttachToFrameBuffer();
		UnBind();
		m_texture_attachment = texture;
		return m_texture_attachment;
	}

	void FrameBuffer::CreateRenderBufferAttachment(int width, int height)
	{
		m_has_render_buffer_attachment = true;
		m_render_buffer.Bind();
		m_render_buffer.MakeStorage(width, height);
		RenderBuffer::UnBind();
		Bind();
		m_render_buffer.AttachToFrameBuffer();
		UnBind();
	}

}
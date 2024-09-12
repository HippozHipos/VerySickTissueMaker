#include <glad/glad.h>

#include "RenderBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	void RenderBuffer::Init()
	{
		glGenRenderbuffers(1, &m_buffer_id);
	}

	void RenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_buffer_id);
	}

	void RenderBuffer::Destroy()
	{
		glDeleteRenderbuffers(1, &m_buffer_id);
	}

	void RenderBuffer::UnBind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void RenderBuffer::MakeStorage(int width, int height)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height);
	}

	void RenderBuffer::AttachToFrameBuffer()
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_buffer_id);
	}

}
#include <glad/glad.h>

#include "RenderBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	vstmr::RenderBuffer::RenderBuffer()
	{
		glGenRenderbuffers(1, &m_buffer_id);
		CheckOpenGLError();
	}

	void RenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_buffer_id);
		CheckOpenGLError();
	}

	void RenderBuffer::UnBind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		CheckOpenGLError();
	}

	void RenderBuffer::MakeStorage(int widht, int height)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, 800, 600);
		CheckOpenGLError();
	}

	void RenderBuffer::AttachToFrameBuffer()
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_buffer_id);
		CheckOpenGLError();
	}

}
#include "MainPlatformWindowRenderer.h"
#include "Graphics.h"
#include "ResourceLoader/ResourcePathHandler.h"

namespace be {

	MainPlatformWindowRenderer::MainPlatformWindowRenderer(int width, int height)
	{
		m_frame_buffer.Init();

		m_vertex_array.Init(); m_vertex_array.Bind();
		m_vertex_buffer.Init(); m_vertex_buffer.Bind();
		m_index_buffer.Init(); m_index_buffer.Bind();	

		m_vertex_buffer.BufferData(m_quad.GetVertexData(), m_quad.GetVertexBufferSize(), true);
		m_index_buffer.BufferData(m_quad.GetIndexData(), m_quad.GetIndexBufferSize(), true);

		m_vertex_array.SetupLayout<float>(2);
		m_vertex_array.SetupLayout<float>(2);
		m_vertex_array.AddLayout();

		ResizeContext(width, height);

		std::string vertexShaderPath = ResourcePathHandler::GetShadersPath() + "quad_vertex_shader.glsl";
		std::string fragShaderPath = ResourcePathHandler::GetShadersPath() + "quad_fragment_shader.glsl";
		m_shaders.SetVertexShaderPath(vertexShaderPath.c_str());
		m_shaders.SetFragmentShaderPath(fragShaderPath.c_str());
		m_shaders.RecompileShader();
	}

	void MainPlatformWindowRenderer::ResizeContext(int width, int height)
	{
		m_frame_buffer.Bind();
		m_frame_buffer.CreateAttachments(width, height);
		Graphics::UpdateViewport(0, 0, width, height);
	}

	int MainPlatformWindowRenderer::GetWidth()
	{
		return m_frame_buffer.GetWidth();
	}

	int MainPlatformWindowRenderer::GetHeight()
	{
		return m_frame_buffer.GetHeight();
	}

	Quad& MainPlatformWindowRenderer::GetQuad()
	{
		return m_quad;
	}

	void MainPlatformWindowRenderer::BindFrameBuffer()
	{
		m_frame_buffer.Bind();
	}

	void MainPlatformWindowRenderer::Render()
	{
		m_vertex_array.Bind();
		m_index_buffer.Bind();
		m_shaders.Use();
		m_shaders.SetInt("sampler2d", 0);
		Graphics::SetActiveTextureSlot(GL_TEXTURE0);
		m_frame_buffer.GetTexture().Bind();
		Graphics::DrawIndexedTraingles(m_quad.GetIndexBufferCount());
		VertexArray::UnBind();
		FrameBuffer::UnBind();
	}
}

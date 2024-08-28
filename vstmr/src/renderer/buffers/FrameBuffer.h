#include "renderer/Texture.h"
#include "RenderBuffer.h"

namespace vstmr {

	class FrameBuffer
	{
	public:
		FrameBuffer();

	public:
		void Bind();
		static void UnBind();
		void Destroy();

		bool HasTextureAttachment();
		bool HasRenderBufferAttachment();

		Texture CreateTextureAttachment(int width, int height);
		void CreateRenderBufferAttachment(int width, int height);

	private:
		Texture m_texture_attachment;
		RenderBuffer m_render_buffer;

		bool m_has_texture_attachment;
		bool m_has_render_buffer_attachment;

		unsigned int m_buffer_id;
	};

}
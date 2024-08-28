#include "renderer/Texture.h"
#include "RenderBuffer.h"

namespace vstmr {

	class FrameBuffer
	{
	public:
		FrameBuffer() = default;

	public:
		void Init();
		void Bind();
		static void UnBind();
		void Destroy();

		bool HasTextureAttachment();
		bool HasRenderBufferAttachment();

		Texture CreateTextureAttachment(int width, int height);
		void CreateRenderBufferAttachment(int width, int height);

	private:
		Texture m_texture_attachment{};
		RenderBuffer m_render_buffer{};

		bool m_has_texture_attachment = false;
		bool m_has_render_buffer_attachment = false;

		unsigned int m_buffer_id{};
	};

}
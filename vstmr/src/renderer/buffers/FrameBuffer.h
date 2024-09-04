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
		void SetChannels(int format);

		bool HasTextureAttachment();
		bool HasRenderBufferAttachment();

		Texture CreateTextureAttachment(int width, int height);
		void CreateRenderBufferAttachment(int width, int height);

	private:
		Texture m_texture_attachment{};
		RenderBuffer m_render_buffer{};

		bool m_has_texture_attachment = false;
		bool m_has_render_buffer_attachment = false;

		uint8_t m_channels = 3;
		unsigned int m_buffer_id{};
	};

}
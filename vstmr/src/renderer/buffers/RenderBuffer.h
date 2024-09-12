#pragma once

namespace vstmr {

	class RenderBuffer
	{
	public:
		RenderBuffer() = default;

	public:
		void Init();
		void Bind();
		static void UnBind();
		void Destroy();
		void MakeStorage(int widht, int height);
		void AttachToFrameBuffer();

	private:
		unsigned int m_buffer_id;
	};
}
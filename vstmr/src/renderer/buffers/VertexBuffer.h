#pragma once
#include <stdint.h>

namespace vstmr
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;

	public:
		void Init();
		void Bind();
		void BufferData(void* data, size_t size, bool staticDraw = false);
		void BufferSubData(void* data, size_t size, size_t offset);
		void Destroy();
		static void UnBind();

	private:
		unsigned int m_buffer_id;
	};
}
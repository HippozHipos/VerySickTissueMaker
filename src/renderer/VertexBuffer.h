#pragma once
#include <stdint.h>

namespace vstm
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

	public:
		void Bind();
		void BufferData(size_t size, bool staticDraw = false);
		void BufferSubData(void* data, size_t size, size_t offset);
		void Destroy();
		static void UnBind();

	private:
		unsigned int m_buffer;
	};
}
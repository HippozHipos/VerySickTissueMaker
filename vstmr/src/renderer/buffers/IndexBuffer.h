#pragma once
#include <stdint.h>

namespace vstmr
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

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
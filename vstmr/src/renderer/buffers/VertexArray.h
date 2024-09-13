#pragma once

#include <glad/glad.h>

#include <vector>
#include <functional>
#include <stdint.h>

namespace be {

	class VertexArray
	{
	public:
		VertexArray() = default;

	public:
		void Bind();
		void Init();
		static void UnBind();
		void Destroy();

		template<class T> void SetupLayout(int count, bool normalize = false);

		template<> void SetupLayout<float>(int count, bool normalize)
		{
			layoutAdders.push_back([=](GLuint index)
				{
					glVertexAttribPointer(index, count, GL_FLOAT, normalize ? GL_TRUE : GL_FALSE,
						stride, (void*)attribStart);
					attribStart += count * sizeof(float);
				}
			);
			stride += count * sizeof(float);
		};

		template<> void SetupLayout<double>(int count, bool normalize)
		{
			layoutAdders.push_back([=](GLuint index)
				{
					glVertexAttribPointer(index, count, GL_DOUBLE, normalize ? GL_TRUE : GL_FALSE,
						stride, (void*)attribStart);
					attribStart += count * sizeof(double);
				}
			);
			stride += count * sizeof(double);
		};

		template<> void SetupLayout<unsigned char>(int count, bool normalize)
		{
			layoutAdders.push_back([=](GLuint index)
				{
					glVertexAttribPointer(index, count, GL_UNSIGNED_BYTE, normalize ? GL_TRUE : GL_FALSE,
						stride, (void*)attribStart);
					attribStart += count * sizeof(unsigned char);
				}
			);
			stride += count * sizeof(unsigned char);
		};

		template<> void SetupLayout<int>(int count, bool normalize)
		{
			layoutAdders.push_back([=](GLuint index)
				{
					glVertexAttribPointer(index, count, GL_UNSIGNED_INT, normalize ? GL_TRUE : GL_FALSE,
						stride, (void*)attribStart);
					attribStart += count * sizeof(int);
				}
			);
			stride += count * sizeof(int);
		};

		//reminder: we do it like this so that we can reach the end, get the total stride and then start calling  
		//glVertexAttribPointer with that stride
		void AddLayout()
		{
			for (int i = 0; i < layoutAdders.size(); i++)
			{
				layoutAdders[i](i);
				glEnableVertexAttribArray(i);
			}
		}

	private:
		uint64_t attribStart = 0;
		uint64_t stride = 0;
		std::vector<std::function<void(unsigned int)>> layoutAdders;
		unsigned int m_buffer_id = 0;
	};
}
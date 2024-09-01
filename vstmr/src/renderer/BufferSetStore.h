#pragma once

#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>

#include "diagnostics/Logger.h"

#include "GlPrimitivesConversion.h"

#include "buffers/IndexBuffer.h"
#include "buffers/VertexBuffer.h"
#include "buffers/VertexArray.h"

namespace vstmr {


	class BufferSetStore
	{
	public:
		using Unused = std::nullptr_t;

		enum
		{
			EMPTY,
			VERTEX,
			NORMAL,
			COLOR,
			TEXTURE
		};

	private:
		struct BufferSetId
		{
			uint8_t content[4];  //is it vertex, normal, color or texture
			uint8_t type[4]; //actual type like GL_FLOAT, GL_INT etc

			bool operator==(const BufferSetId& other) const
			{
				uint32_t* c = (uint32_t*)&content;
				uint32_t* t = (uint32_t*)&type;
				return *c == *t;
			}

			bool operator!=(const BufferSetId& other) const
			{
				return !(*this == other);
			}
		};

		struct BufferSetIdHash
		{
			std::size_t operator()(const BufferSetId& id) const
			{
				uint32_t* c = (uint32_t*)&id.content;
				uint32_t* t = (uint32_t*)&id.type;

				return ((std::hash<uint32_t>()(*c)
					^ (std::hash<uint32_t>()(*t) << 1)) >> 1);
			}
		};

		struct BufferSet
		{
			VertexBuffer vertex_buffer{};
			IndexBuffer index_buffer{};
			VertexArray vertex_array{};
		};

	public:
		void SetVertexData(void* data, size_t size);
		void SetIndexData(void* data, size_t size);
		void SetColorChannels(int channels);
		void SetNumAxis(int axis);

		template<class T1, class T2, class T3, class T4, class... Types>
		BufferSetId GetUniqueBufferSetId(Types... types)
		{
			BufferSetId id;

			if (!std::is_same_v<T1, Unused>)
				id.type[0] = GlPrimitiveConvert<T1>();
			if (!std::is_same_v<T2, Unused>)
				id.type[1] = GlPrimitiveConvert<T2>();
			if (!std::is_same_v<T3, Unused>)
				id.type[2] = GlPrimitiveConvert<T3>();
			if (!std::is_same_v<T4, Unused>)
				id.type[3] = GlPrimitiveConvert<T4>();

			int i = 0;
			(
				[&]
				{
					id.content[i++] = types;
				} (), ...
			);

			return id;
		}

		template<class T1, class T2, class T3, class T4, class... Types>
		std::unordered_map<BufferSetId, BufferSet>::iterator 
			GetBufferSet(Types... types)
		{
			VSTM_ASSERT(sizeof...(types) >= 1, "Vertex buffer must have at-least one attribute");
			([&] { VSTM_ASSERT(types != EMPTY, "First attribute in vertex buffer cannot be empty"); return; } (), ...);
			return GetBufferSetFromId(GetUniqueBufferSetId<T1, T2, T3, T4>(types...));
		}

		template<class T1, class T2, class T3, class T4, class... Types>
		void AddBufferSet(Types... types)
		{
			VSTM_ASSERT(sizeof...(types) >= 1, "Vertex buffer must have at-least one attribute");
			([&] { VSTM_ASSERT(types != EMPTY, "First attribute in vertex buffer cannot be empty"); return; } (), ...);

			BufferSetId id = GetUniqueBufferSetId<T1, T2, T3, T4>(types...);
			auto bufferIt = m_buffers.find(id);
			if (bufferIt != m_buffers.end())
			{
				uint32_t* c = (uint32_t*)&id.content;
				uint32_t* t = (uint32_t*)&id.type;
				VSTM_CD_LOGWARN("Buffer with id-content: {} and id-type: {} already exists. No action taken", *c, *t);
			}
			else
			{
				BufferSet buffetSet = CreateBufferSet<T1, T2, T3, T4>(id);
			}
		}


		std::unordered_map<BufferSetId, BufferSet>::iterator 
			GetBufferSetFromId(const BufferSetId& id);

	private:
		template<class T1, class T2, class T3, class T4>
		BufferSet CreateBufferSet(const BufferSetId& id)
		{
			BufferSet bufferset;

			bufferset.vertex_array.Bind();

			bufferset.vertex_buffer.Bind();
			bufferset.vertex_buffer.BufferData(m_vertex_data_size);
			bufferset.vertex_buffer.BufferSubData(m_vertex_data, m_vertex_data_size, 0);

			bufferset.index_buffer.Bind();
			bufferset.index_buffer.BufferData(m_index_data_size);
			bufferset.index_buffer.BufferSubData(m_index_data, m_index_data_size, 0);

			int stride = sizeof(T1) * GetContentCount(id.content[0]);
			if (!std::is_same_v<T2, Unused>)
				stride += sizeof(T2) * GetContentCount(id.content[1]);
			if (!std::is_same_v<T3, Unused>)
				stride += sizeof(T3) * GetContentCount(id.content[2]);
			if (!std::is_same_v<T4, Unused>)
				stride += sizeof(T4) * GetContentCount(id.content[3]);

			int attribStart = 0;
			glVertexAttribPointer(0, GetContentCount(id.content[0]), GlPrimitiveConvert<T1>(), GL_FALSE, stride, (void*)attribStart);
			glEnableVertexAttribArray(0);

			if (!std::is_same_v<T2, Unused>)
			{
				attribStart += sizeof(T1) * GetContentCount(id.content[0]);
				glVertexAttribPointer(1, GetContentCount(id.content[1]), GlPrimitiveConvert<T2>(), GL_FALSE, stride, (void*)attribStart);
				glEnableVertexAttribArray(1);
			}
			if (!std::is_same_v<T3, Unused>)
			{
				attribStart += sizeof(T2) * GetContentCount(id.content[1]);
				glVertexAttribPointer(2, GetContentCount(id.content[2]), GlPrimitiveConvert<T3>(), GL_FALSE, stride, (void*)attribStart);
				glEnableVertexAttribArray(2);

			}
			if (!std::is_same_v<T4, Unused>)
			{
				attribStart += sizeof(T3) * GetContentCount(id.content[2]);
				glVertexAttribPointer(3, GetContentCount(id.content[3]), GlPrimitiveConvert<T4>(), GL_FALSE, stride, (void*)attribStart);
				glEnableVertexAttribArray(3);
			}


			//REMINDER: Probably better to unbind everything after creation but leave it commented for now for easier testing
			//VertexBuffer::UnBind();
			//IndexBuffer::UnBind();
			//VertexArray::UnBind();

			return bufferset;
		}

		//second argument of glVertexAttribPointer
		int GetContentCount(int content);

	private:	
		int m_num_axis = 3;
		int m_color_channels = 3;

		void* m_vertex_data = nullptr;
		size_t m_vertex_data_size = 0;

		void* m_index_data = nullptr;
		size_t m_index_data_size = 0;

		std::unordered_map<BufferSetId, BufferSet, BufferSetIdHash> m_buffers;
	};

}

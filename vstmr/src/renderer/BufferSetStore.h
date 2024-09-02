#pragma once

#include <vector>
#include <unordered_map>
#include <bitset>
#include <iostream>

#include "diagnostics/Assert.h"
#include "diagnostics/Logger.h"

#include "GlPrimitivesConversion.h"

#include "buffers/IndexBuffer.h"
#include "buffers/VertexBuffer.h"
#include "buffers/VertexArray.h"

namespace vstmr {

	struct BufferSet
	{
		VertexBuffer vertex_buffer{};
		IndexBuffer index_buffer{};
		VertexArray vertex_array{};
	};

	struct BufferSetId
	{
		uint8_t layout[4];  //is it vertex, normal, color or texture
		uint8_t type[4]; //actual type like GL_FLOAT, GL_INT etc

		bool operator==(const BufferSetId& other) const
		{
			uint32_t* cThis = (uint32_t*)&layout;
			uint32_t* cOther = (uint32_t*)&other.layout;
			uint32_t* tThis = (uint32_t*)&type;
			uint32_t* tOther = (uint32_t*)&other.type;
			return *cThis == *cOther && *tThis == *tOther;
		}

		bool operator!=(const BufferSetId& other) const
		{
			return !(*this == other);
		}
	};

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
		struct BufferSetIdHash
		{
			std::size_t operator()(const BufferSetId& id) const
			{
				uint32_t* c = (uint32_t*)&id.layout;
				uint32_t* t = (uint32_t*)&id.type;
				return ((std::hash<uint32_t>()(*c)
					^ (std::hash<uint32_t>()(*t) << 1)) >> 1);
			}
		};

	public:
		void SetVertexData(void* data, size_t size);
		void SetIndexData(void* data, size_t size);
		void SetColorChannels(int channels);
		void SetBufferLayouts(int l1, int l2, int l3, int l4);
		void SetBufferLayoutTypes(int type1, int type2, int type3, int type4);
		void SetBufferLayouts(int* layouts, size_t size);
		void SetBufferLayoutTypes(int* types, size_t size);
		void SetNumAxis(int axis);

		BufferSetId MakeBufferSetId()
		{
			CheckForTomFoolery();

			BufferSetId id;
			for (size_t i = 0; i < m_num_layouts; i++)
			{
				if (m_buffer_layouts[i] == EMPTY)
					break;
				id.layout[i] = m_buffer_layouts[i];
				id.type[i] = m_buffer_layout_types[i];
			}

			return id;
		}

		std::unordered_map<BufferSetId, BufferSet>::iterator GetBufferSet()
		{
			return GetBufferSetFromId(MakeBufferSetId());
		}

		void AddBufferSet()
		{
			BufferSetId id = MakeBufferSetId();
			auto bufferIt = GetBufferSetFromId(id);
			if (bufferIt != m_buffers.end())
			{
				uint32_t* c = (uint32_t*)&id.layout;
				uint32_t* t = (uint32_t*)&id.type;
				VSTM_CD_LOGWARN("Buffer with id-content: {} and id-type: {} already exists. No action taken", *c, *t);
			}
			else
			{
				BufferSet bufferset = CreateBufferSet(id);
				m_buffers.insert(std::pair<BufferSetId, BufferSet>(id, bufferset));
			}
		}


		std::unordered_map<BufferSetId, BufferSet>::iterator 
			GetBufferSetFromId(const BufferSetId& id);

		std::unordered_map<BufferSetId, BufferSet>::iterator End();

	private:
		void CheckForTomFoolery();

	private:
		BufferSet CreateBufferSet(const BufferSetId& id)
		{
			BufferSet bufferset;
			
			bufferset.vertex_array.Init();
			bufferset.vertex_buffer.Init();
			bufferset.index_buffer.Init();

			bufferset.vertex_array.Bind();

			bufferset.vertex_buffer.Bind();
			bufferset.vertex_buffer.BufferData(m_vertex_data_size);
			bufferset.vertex_buffer.BufferSubData(m_vertex_data, m_vertex_data_size, 0);

			bufferset.index_buffer.Bind();
			bufferset.index_buffer.BufferData(m_index_data_size);
			bufferset.index_buffer.BufferSubData(m_index_data, m_index_data_size, 0);

			int stride = 0; //stride is 0 if theres only 1 layout
			if (m_buffer_layouts[1] != EMPTY)
				stride = GetGLTypeSize(m_buffer_layout_types[0]) * GetContentCount(id.layout[0]) + 
						 GetGLTypeSize(m_buffer_layout_types[1]) * GetContentCount(id.layout[1]);
			if (m_buffer_layouts[2] != EMPTY)
				stride += GetGLTypeSize(m_buffer_layout_types[2]) * GetContentCount(id.layout[2]);
			if (m_buffer_layouts[3] != EMPTY)
				stride += GetGLTypeSize(m_buffer_layout_types[3]) * GetContentCount(id.layout[3]);

			int attribStart = 0;
			for (size_t i = 0; i < m_num_layouts; i++)
			{
				if (m_buffer_layouts[i] == EMPTY)
					break;
				glVertexAttribPointer(i, GetContentCount(id.layout[i]), m_buffer_layout_types[i], GL_FALSE, stride, (void*)attribStart);
				attribStart += GetGLTypeSize(m_buffer_layout_types[i]) * GetContentCount(id.layout[i]);
				glEnableVertexAttribArray(i);
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
		static constexpr size_t m_num_layouts = 4;
		int m_buffer_layouts[4] = { EMPTY, EMPTY, EMPTY, EMPTY };
		int m_buffer_layout_types[4] = { EMPTY, EMPTY, EMPTY, EMPTY };

		int m_num_axis = 3;
		int m_color_channels = 3;

		void* m_vertex_data = nullptr;
		size_t m_vertex_data_size = 0;

		void* m_index_data = nullptr;
		size_t m_index_data_size = 0;

		std::unordered_map<BufferSetId, BufferSet, BufferSetIdHash> m_buffers;
	};

}

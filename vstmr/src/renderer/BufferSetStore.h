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

		BufferSetId MakeBufferSetId();

		std::unordered_map<BufferSetId, BufferSet>::iterator GetBufferSet();
		void AddBufferSet();
		std::unordered_map<BufferSetId, BufferSet>::iterator GetBufferSetFromId(const BufferSetId& id);
		std::unordered_map<BufferSetId, BufferSet>::iterator End();

	private:
		void CheckForTomfoolery();
		BufferSet CreateBufferSet(const BufferSetId& id);
		//second argument of glVertexAttribPointer
		int GetNumLayoutContents(int layout);

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

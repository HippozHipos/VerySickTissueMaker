#include "BufferSetStore.h"

namespace vstmr {

	void BufferSetStore::SetVertexData(void* data, size_t size)
	{
		m_vertex_data = data;
		m_vertex_data_size = size;
	}

	void BufferSetStore::SetIndexData(void* data, size_t size)
	{
		m_index_data = data;
		m_index_data_size = size;
	}

	void BufferSetStore::SetColorChannels(int channels)
	{
		m_color_channels = channels;
	}

	void BufferSetStore::SetNumAxis(int axis)
	{
		m_num_axis = axis;
	}

	void BufferSetStore::SetBufferConstructionTypes(int type1, int type2, int type3, int type4)
	{
		m_buffer_layout_types[0] = type1;
		m_buffer_layout_types[1] = type2;
		m_buffer_layout_types[2] = type3;
		m_buffer_layout_types[3] = type4;
	}

	void BufferSetStore::SetBufferConstructionLayouts(int l1, int l2, int l3, int l4)
	{
		m_buffer_layouts[0] = l1;
		m_buffer_layouts[1] = l2;
		m_buffer_layouts[2] = l3;
		m_buffer_layouts[3] = l4;
	}

	void BufferSetStore::SetBufferConstructionLayouts(int* types, size_t size = m_num_layouts)
	{
		for (size_t i = 0; i < size; i++)
			m_buffer_layouts[0] = types[i];
	}

	void BufferSetStore::SetBufferConstructionTypes(int* layouts, size_t size = m_num_layouts)
	{
		for (size_t i = 0; i < size; i++)
			m_buffer_layout_types[0] = layouts[i];
	}

	std::unordered_map<BufferSetId, BufferSet>::iterator 
		BufferSetStore::GetBufferSetFromId(const BufferSetId& id)
	{
		return m_buffers.find(id);
	}

	std::unordered_map<BufferSetId, BufferSet>::iterator
		BufferSetStore::End()
	{
		return m_buffers.end();
	}

	void BufferSetStore::CheckForTomFoolery()
	{
		for (size_t i = 0; i < m_num_layouts; i++)
		{
			VSTMR_ASSERT(m_buffer_layouts[0] != EMPTY && m_buffer_layout_types[0] != EMPTY,
				"Buffer must at-least have one layout");

			if ((m_buffer_layouts[i] == EMPTY && m_buffer_layout_types[i] != EMPTY) ||
				(m_buffer_layouts[i] != EMPTY && m_buffer_layout_types[i] == EMPTY))
			{
				VSTMR_ASSERT(false, "Mismatch in buffer layout and types");
			}
		}
	}

	int BufferSetStore::GetContentCount(int content)
	{
		switch (content)
		{
			case NORMAL: return m_num_axis;
			case VERTEX: return m_num_axis;
			case COLOR: return m_color_channels;
			case TEXTURE: return 2;
		}
		VSTMR_ASSERT(false, "Unsupported content: {}", content);
	}

}
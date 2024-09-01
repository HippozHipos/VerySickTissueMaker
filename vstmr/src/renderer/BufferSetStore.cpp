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

	std::unordered_map<BufferSetStore::BufferSetId, BufferSetStore::BufferSet>::iterator
		BufferSetStore::GetBufferSetFromId(const BufferSetId& id)
	{
		return m_buffers.find(id);
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
		VSTM_ASSERT(false, "Unsupported content: {}", content);
	}

}
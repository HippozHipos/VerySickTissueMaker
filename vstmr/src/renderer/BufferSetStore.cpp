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

	void BufferSetStore::SetBufferLayoutTypes(int type1, int type2, int type3, int type4)
	{
		m_buffer_layout_types[0] = type1;
		m_buffer_layout_types[1] = type2;
		m_buffer_layout_types[2] = type3;
		m_buffer_layout_types[3] = type4;
	}

	void BufferSetStore::SetBufferLayouts(int l1, int l2, int l3, int l4)
	{
		m_buffer_layouts[0] = l1;
		m_buffer_layouts[1] = l2;
		m_buffer_layouts[2] = l3;
		m_buffer_layouts[3] = l4;
	}

	void BufferSetStore::SetBufferLayouts(int* types, size_t size = m_num_layouts)
	{
		for (size_t i = 0; i < size; i++)
			m_buffer_layouts[0] = types[i];
	}

	void BufferSetStore::SetBufferLayoutTypes(int* layouts, size_t size = m_num_layouts)
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

	void BufferSetStore::CheckForTomfoolery()
	{
		VSTMR_ASSERT(m_buffer_layouts[0] != EMPTY && m_buffer_layout_types[0] != EMPTY,
			"Buffer must at-least have one layout");

		for (size_t i = 0; i < m_num_layouts; i++)
		{
			if ((m_buffer_layouts[i] == EMPTY && m_buffer_layout_types[i] != EMPTY) ||
				(m_buffer_layouts[i] != EMPTY && m_buffer_layout_types[i] == EMPTY))
			{
				VSTMR_ASSERT(false, "Mismatch in buffer layout and types");
			}
		}
	}

	int BufferSetStore::GetNumLayoutContents(int layout)
	{
		switch (layout)
		{
			case NORMAL: return m_num_axis;
			case VERTEX: return m_num_axis;
			case COLOR: return m_color_channels;
			case TEXTURE: return 2;
		}
		VSTMR_ASSERT(false, "Unsupported content: {}", layout);
	}

	BufferSetId BufferSetStore::MakeBufferSetId()
	{
		CheckForTomfoolery();

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

	std::unordered_map<BufferSetId, BufferSet>::iterator BufferSetStore::GetBufferSet()
	{
		return GetBufferSetFromId(MakeBufferSetId());
	}

	void BufferSetStore::AddBufferSet()
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

	BufferSet BufferSetStore::CreateBufferSet(const BufferSetId& id)
	{
		BufferSet bufferset;

		bufferset.vertex_array.Init();
		bufferset.vertex_buffer.Init();
		bufferset.index_buffer.Init();

		bufferset.vertex_array.Bind();

		bufferset.vertex_buffer.Bind();
		bufferset.vertex_buffer.BufferData(m_vertex_data, m_vertex_data_size, false);

		bufferset.index_buffer.Bind();
		bufferset.index_buffer.BufferData(m_index_data, m_index_data_size, false);


		int stride = 0; //stride is 0 if theres only 1 layout
		if (m_buffer_layouts[1] != EMPTY)
			stride = GetGLTypeSize(m_buffer_layout_types[0]) * GetNumLayoutContents(id.layout[0]) +
			GetGLTypeSize(m_buffer_layout_types[1]) * GetNumLayoutContents(id.layout[1]);
		if (m_buffer_layouts[2] != EMPTY)
			stride += GetGLTypeSize(m_buffer_layout_types[2]) * GetNumLayoutContents(id.layout[2]);
		if (m_buffer_layouts[3] != EMPTY)
			stride += GetGLTypeSize(m_buffer_layout_types[3]) * GetNumLayoutContents(id.layout[3]);

		int attribStart = 0;
		for (size_t i = 0; i < m_num_layouts; i++)
		{
			if (m_buffer_layouts[i] == EMPTY)
				break;
			glVertexAttribPointer(i, GetNumLayoutContents(id.layout[i]), m_buffer_layout_types[i], GL_FALSE, stride, (void*)attribStart);
			attribStart += GetGLTypeSize(m_buffer_layout_types[i]) * GetNumLayoutContents(id.layout[i]);
			glEnableVertexAttribArray(i);
		}

		//REMINDER: Probably better to unbind everything after creation but leave it commented for now for easier testing
		//VertexBuffer::UnBind();
		//IndexBuffer::UnBind();
		//VertexArray::UnBind();

		return bufferset;
	}

}
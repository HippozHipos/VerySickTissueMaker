#include <glm/glm.hpp>

#include "MeshComponent.h"

namespace vstmr {

	int MeshComponent::IndexBufferSize()
	{
		return index_data.size();
	}

	int MeshComponent::VertexBufferSize()
	{
		return vertex_data.size() * Stride();
	}

	int MeshComponent::Stride()
	{
		return sizeof(VertexData);
	}

	void MeshComponent::SetupMesh()
	{
		vertex_array.Init();
		vertex_buffer.Init();
		index_buffer.Init();

		vertex_array.Bind();

		vertex_buffer.Bind();
		vertex_buffer.BufferData((void*)vertex_data.data(), VertexBufferSize(), is_dynamic);

		index_buffer.Bind();
		index_buffer.BufferData((void*)index_data.data(), IndexBufferSize(), is_dynamic);

		int sizes[4] = { 3, 3, 2, 3 };
		int attribStart = 0;
		for (int i = 0; i < 4; i++)
		{
			glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, Stride(), (void*)attribStart);
			attribStart += sizeof(float) * sizes[i];
			glEnableVertexAttribArray(i);
		}

		//UNCOMMENT LATER
		/*vertex_array.UnBind();
		vertex_buffer.UnBind();
		index_buffer.UnBind();*/
	}

}
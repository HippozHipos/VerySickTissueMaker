#include <glm/glm.hpp>

#include "Mesh.h"

namespace be {

	int Mesh::IndexBufferSize()
	{
		return index_data.size() * sizeof(unsigned int);
	}

	int Mesh::VertexBufferSize()
	{
		return vertex_data.size() * Stride();
	}

	int Mesh::Stride()
	{
		return sizeof(VertexData);
	}

	void Mesh::SetupMesh()
	{
		vertex_array.Init();
		vertex_buffer.Init();
		index_buffer.Init();

		vertex_array.Bind();

		vertex_buffer.Bind();
		vertex_buffer.BufferData((void*)vertex_data.data(), VertexBufferSize(), is_dynamic);

		index_buffer.Bind();
		index_buffer.BufferData((void*)index_data.data(), IndexBufferSize(), is_dynamic);

		vertex_array.SetupLayout<float>(3);
		vertex_array.SetupLayout<float>(3);
		vertex_array.SetupLayout<float>(2);
		vertex_array.AddLayout();

		vertex_array.UnBind();
		vertex_buffer.UnBind();
		index_buffer.UnBind();
	}

}
#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "ECS/Component.h"

#include "renderer/buffers/VertexArray.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"

namespace vstmr {
	
	struct MeshComponent : public Component
	{
		struct VertexData
		{
			glm::vec3 vertices;
			glm::vec3 normals;
			glm::vec2 texture;
			glm::vec3 color;
		};

		int IndexBufferSize();
		int VertexBufferSize();
		int Stride();
		void SetupMesh();

		std::vector<VertexData> vertex_data;
		std::vector<uint32_t> index_data;
		VertexArray vertex_array;
		VertexBuffer vertex_buffer;
		IndexBuffer index_buffer;
		bool is_dynamic = false;
	};

}
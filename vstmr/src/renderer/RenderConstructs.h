#include <vector>

namespace vstmr {

	struct Vertex
	{
		float vertex[3];
		float normals[3];
		float texture[2];
		float color[3];
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

}
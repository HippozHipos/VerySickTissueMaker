#include "MeshRenderer.h"


#include "Diagnostics/Logger.h"

namespace be {

	int MeshRenderer::GetVertexCount()
	{
		int verts = 0;
		for (int i = 0; i < meshes.size(); i++)
		{
			verts += meshes[i].vertex_data.size();
		}
		return verts;
	}

	int MeshRenderer::GetIndexCount()
	{
		int indices = 0;
		for (int i = 0; i < meshes.size(); i++)
		{
			indices += meshes[i].index_data.size();
		}
		return indices;
	}

}
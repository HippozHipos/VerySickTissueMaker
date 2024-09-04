#include "MeshLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "diagnostics/Logger.h"

namespace vstmr {

	//Very basic for now - just loads vertex position and index data
	void MeshLoader::Load(const char* path, MeshComponent& mesh)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VSTM_CON_LOGERROR("ERROR::ASSIMP::{}", importer.GetErrorString());
			return;
		}

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* assMesh = scene->mMeshes[i];
			for (int j = 0; j < assMesh->mNumVertices; j++)
			{
				MeshComponent::VertexData vd;
				vd.vertices.x = assMesh->mVertices[j].x;
				vd.vertices.y = assMesh->mVertices[j].y;
				vd.vertices.z = assMesh->mVertices[j].z;
				mesh.vertex_data.push_back(vd);
			}
			for (int j = 0; j < assMesh->mNumFaces; j++)
			{
				aiFace face = assMesh->mFaces[j];
				for (int k = 0; k < face.mNumIndices; k++)
				{
					mesh.index_data.push_back(face.mIndices[k]);
				}
			}
		}
	}
}
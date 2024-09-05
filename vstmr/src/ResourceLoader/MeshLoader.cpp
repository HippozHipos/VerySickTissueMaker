#include "MeshLoader.h"
#include "diagnostics/Logger.h"

namespace vstmr {

	//Very basic for now - just loads vertex position and index data
	void MeshLoader::Load(const char* path, std::vector<MeshComponent>& meshes)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VSTM_CD_LOGERROR("ERROR", importer.GetErrorString());
			return;
		}

		ProcessNode(scene->mRootNode, scene, meshes);
	}

	void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<MeshComponent>& meshes)
	{
		MeshComponent mesh;
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* assMesh = scene->mMeshes[node->mMeshes[i]];
			for (int j = 0; j < assMesh->mNumVertices; j++)
			{
				MeshComponent::VertexData vd;

				vd.vertices.x = assMesh->mVertices[j].x;
				vd.vertices.y = assMesh->mVertices[j].y;
				vd.vertices.z = assMesh->mVertices[j].z;

				if (assMesh->mNormals)
				{
					vd.normals.x = assMesh->mNormals[j].x;
					vd.normals.y = assMesh->mNormals[j].y;
					vd.normals.z = assMesh->mNormals[j].z;
				}

				if (assMesh->mTextureCoords[0])
				{
					vd.texture.x = assMesh->mTextureCoords[0][j].x;
					vd.texture.y = assMesh->mTextureCoords[0][j].y;
				}
				else
				{
					vd.texture = glm::vec2(0.0f, 0.0f);
				}
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
		meshes.push_back(mesh);
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, meshes);
		}
	}
}
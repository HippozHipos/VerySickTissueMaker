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
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            MeshComponent mesh;
            aiMesh* assMesh = scene->mMeshes[node->mMeshes[i]];

            mesh.vertex_data.reserve(assMesh->mNumVertices);
            for (unsigned int j = 0; j < assMesh->mNumVertices; j++)
            {
                MeshComponent::VertexData vd;
                vd.vertices = glm::vec3(assMesh->mVertices[j].x, assMesh->mVertices[j].y, assMesh->mVertices[j].z);

                if (assMesh->mNormals)
                {
                    vd.normals = glm::vec3(assMesh->mNormals[j].x, assMesh->mNormals[j].y, assMesh->mNormals[j].z);
                }

                if (assMesh->mTextureCoords[0])
                {
                    vd.texture = glm::vec2(assMesh->mTextureCoords[0][j].x, assMesh->mTextureCoords[0][j].y);
                }
                else
                {
                    vd.texture = glm::vec2(0.0f, 0.0f);
                }

                mesh.vertex_data.push_back(vd);
            }

            mesh.index_data.reserve(assMesh->mNumFaces * 3);
            for (unsigned int j = 0; j < assMesh->mNumFaces; j++)
            {
                aiFace face = assMesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; k++)
                {
                    mesh.index_data.push_back(face.mIndices[k]);
                }
            }

            if (!mesh.vertex_data.empty() && !mesh.index_data.empty())
            {
                meshes.push_back(std::move(mesh));
            }
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene, meshes);
        }
    }
}
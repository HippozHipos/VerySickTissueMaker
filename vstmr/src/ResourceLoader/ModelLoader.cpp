#include "ModelLoader.h"
#include "diagnostics/Logger.h"
#include "diagnostics/assert.h"

namespace be {

    std::filesystem::path ModelLoader::m_path_to_assets{};

	void ModelLoader::Load(const char* path, MeshRenderer& renderer, TextureManager& texmanager)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VSTM_CD_LOGERROR("Mesh loading error", importer.GetErrorString());
			return;
		}

		ProcessNode(scene->mRootNode, scene, renderer, texmanager);
        if (renderer.material.textures.size() > renderer.meshes.size())
            assert(false && "Mesh loading failed due to incorrect data");

        int missing = renderer.meshes.size() - renderer.material.textures.size();
        VSTM_CD_LOGWARN("{} default textures used for the model", missing);
        for (int i = 0; i < missing; i++)
        {
            renderer.material.textures.push_back(texmanager.Get("default"));
        }
	}

    void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, MeshRenderer& renderer, TextureManager& texmanager)
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
                renderer.meshes.push_back(std::move(mesh));
            }

            if (assMesh->mMaterialIndex >= 0)
            {
                LoadTextures(scene, assMesh, renderer, texmanager);
            }
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene, renderer, texmanager);
        }
    }

    void ModelLoader::LoadTextures(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager)
    {
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_DIFFUSE);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_SPECULAR);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_NORMALS);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_AMBIENT);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_HEIGHT);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_EMISSIVE);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_OPACITY);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_METALNESS);
        LoadTexture(scene, assMesh, renderer, texmanager, aiTextureType_DIFFUSE_ROUGHNESS);
    }


    void ModelLoader::LoadTexture(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager, aiTextureType type)
    {
        aiMaterial* material = scene->mMaterials[assMesh->mMaterialIndex];
        if (!material) return;

        for (unsigned int j = 0; j < material->GetTextureCount(type); j++)
        {
            aiString path;
            if (material->GetTexture(type, j, &path) == AI_SUCCESS)
            {
                std::string fullpath = m_path_to_assets.string() + path.C_Str();
                Texture texture = texmanager.Load(fullpath, fullpath, true); // Use path as texture name
                renderer.material.textures.push_back(texture);
            }
            else
            {
                VSTM_CD_LOGERROR("Failed to get texture of type", static_cast<int>(type), "for material index", assMesh->mMaterialIndex);
            }
        }
    }

    void ModelLoader::SetAssetsFolderPath(const std::filesystem::path& path)
    {
        m_path_to_assets = path;
    }

}
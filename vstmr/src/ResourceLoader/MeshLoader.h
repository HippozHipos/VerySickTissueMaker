#pragma once

#include "renderer/MeshRenderer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "renderer/Texture.h"

namespace vstmr {

	class MeshLoader
	{
	public:
		static void Load(const char* path, MeshRenderer& renderer, TextureManager& texmanager);

	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, MeshRenderer& renderer, TextureManager& texmanager);
		static void LoadTextures(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager);
		static void LoadTexture(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager, aiTextureType type);
		//static void LoadTextures();
	};

}
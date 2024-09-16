#pragma once
#include "pch.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Renderer/MeshRenderer.h"
#include "Renderer/Texture.h"

namespace be {

	class ModelLoader
	{
	public:
		static void Load(const char* path, MeshRenderer& renderer, TextureManager& texmanager);

	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, MeshRenderer& renderer, TextureManager& texmanager);
		static void LoadTextures(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager);
		static void LoadTexture(const aiScene* scene, const aiMesh* assMesh, MeshRenderer& renderer, TextureManager& texmanager, aiTextureType type);
	};

}
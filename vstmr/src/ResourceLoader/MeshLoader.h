#pragma once

#include "renderer/MeshComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace vstmr {

	class MeshLoader
	{
	public:
		static void Load(const char* path, std::vector<MeshComponent>& meshes);

	private:
		static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<MeshComponent>& meshes);
	};

}
#pragma once

#include "renderer/MeshComponent.h"

namespace vstmr {

	class MeshLoader
	{
	public:
		static void Load(const char* path, MeshComponent& mesh);
	};

}
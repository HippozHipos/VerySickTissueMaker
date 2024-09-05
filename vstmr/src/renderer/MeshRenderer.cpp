#include "MeshRenderer.h"
#include "MeshComponent.h"
#include "Material.h"

#include "diagnostics/Logger.h"

namespace vstmr {

	MeshRenderer::MeshRenderer()
	{
		AddComponent<VectorComponent<MeshComponent>>();
		AddComponent<Material>();
	}

}
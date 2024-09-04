#include "MeshRenderer.h"
#include "MeshComponent.h"

#include "diagnostics/Logger.h"

namespace vstmr {

	MeshRenderer::MeshRenderer()
	{
		AddComponent<MeshComponent>();
	}

	void MeshRenderer::Start()
	{
		VSTM_CD_LOGINFO("Mesh renderer start");
	}

}
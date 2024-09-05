#include "BehaviourProcessor.h"

#include "ECS/Behaviour.h"
#include "MeshRendererProcessor.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"
#include "diagnostics/OpenglError.h"
#include "renderer/Renderer.h"
#include "renderer/Material.h"

#include "ECS/ECS.h"

namespace vstmr {

	void BehaviourProcessor::Execute()
	{
		auto view = ECS::registry.view<MeshRenderer>();
	}

}

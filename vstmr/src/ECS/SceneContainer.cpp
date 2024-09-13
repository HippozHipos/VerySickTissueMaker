#include "SceneContainer.h"
#include "diagnostics/Logger.h"
#include "BehaviouralSceneObject.h"

namespace be {

	SceneContainer::SceneContainer() 
	{
		m_entity = ECS::registry.create();
	}

}
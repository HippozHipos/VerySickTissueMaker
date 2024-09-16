#include "SceneContainer.h"
#include "Diagnostics/Logger.h"
#include "BehaviouralSceneObject.h"

namespace be {

	SceneContainer::SceneContainer() 
	{
		m_entity = ECS::registry.create();
	}

}
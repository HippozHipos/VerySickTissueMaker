#include "SceneContainer.h"
#include "Diagnostics/Logger.h"
#include "Behaviour/BehaviourObject.h"

namespace be {

	SceneContainer::SceneContainer() 
	{
		m_entity = ECS::registry.create();
	}

}
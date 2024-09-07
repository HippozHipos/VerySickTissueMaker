#include "SceneContainer.h"
#include "diagnostics/Logger.h"
namespace vstmr {

	SceneContainer::SceneContainer() 
	{
		m_entity = ECS::registry.create();
	}
}
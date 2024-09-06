#include "SceneContainer.h"
#include "diagnostics/Logger.h"
namespace vstmr {

	SceneContainer::SceneContainer() 
	{
		_SetEntity(ECS::registry.create());
	}

	void SceneContainer::_SetEntity(entt::entity entity)
	{
		m_entity = entity;
	}
}
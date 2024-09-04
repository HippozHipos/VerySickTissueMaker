#include "SceneContainer.h"

namespace vstmr {

	SceneContainer::SceneContainer() :
		m_entity{ 0 }
	{
	}

	SceneContainer::SceneContainer(entt::entity entity) :
		m_entity{ entity }
	{
	}

	void SceneContainer::_SetEntity(entt::entity entity)
	{
		m_entity = entity;
	}
}
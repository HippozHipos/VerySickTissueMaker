#include "RootSceneContainer.h"

namespace vstmr {

	RootSceneContainer::RootSceneContainer()
	{
		_SetEntity(ECS::registry.create());
	}

	SceneContainer& RootSceneContainer::CreateSceneContainer()
	{
		SceneContainer& sc = AddComponent<SceneContainer>(ECS::registry.create());
		return sc;
	}

}
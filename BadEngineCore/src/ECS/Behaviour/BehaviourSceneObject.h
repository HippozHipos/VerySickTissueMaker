#pragma once

#include "BehaviourProvider.h"
#include "ECS/SceneObject.h"

namespace be {

	template<class Derived>
	class BehaviourSceneObject : public SceneObject, public BehaviourProvider<Derived> {};

}
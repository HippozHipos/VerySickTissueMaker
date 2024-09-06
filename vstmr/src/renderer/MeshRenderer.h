#pragma once

#include "ECS/Component.h"

namespace vstmr {

	//probably a good idea to turn this into a general-use VectorComponent since i imagine
	//we will need it else where as well
	template<class T>
	class VectorComponent : public Component
	{
	public:
		std::vector<T> vector;
	};

	class MeshRenderer : public SceneContainer
	{
	public:
		MeshRenderer();

	};

}
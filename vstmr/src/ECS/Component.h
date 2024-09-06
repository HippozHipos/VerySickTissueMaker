#pragma once
#include "SceneContainer.h"

namespace vstmr {

	class Component : public SceneContainer
	{
	public:
		virtual ~Component() = default;
	};

}
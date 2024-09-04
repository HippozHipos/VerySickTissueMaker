#pragma once

#include "Shaders.h"
#include "ECS/Component.h"

namespace vstmr {

	class Material : public Component
	{
	public:
		Material();

	public:
		Shaders shaders;
	};

}
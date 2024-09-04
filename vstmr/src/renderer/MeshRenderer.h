#pragma once

#include "ECS/Behaviour.h"

namespace vstmr {

	class MeshRenderer : public Behaviour
	{
	public:
		MeshRenderer();

	public:
		void Start() override;
	};

}
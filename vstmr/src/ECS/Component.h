#pragma once

#include "Behaviour.h"

namespace vstmr {

	class Component : public Behaviour
	{
	public:
		virtual ~Component() = default;
	};

}
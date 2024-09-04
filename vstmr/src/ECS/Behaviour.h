#pragma once

#include "SceneContainer.h"

namespace vstmr {

	class Behaviour : public SceneContainer
	{
	public:
		virtual ~Behaviour() = default;

	protected:
		virtual void Start();
		virtual void Update();
		virtual void End();
		virtual void Gui();
	};

}
#pragma once

#include <string>
#include <memory>

#include "Shaders.h"
#include "BufferSetStore.h"

#include "ECS/Component.h"
#include "camera/Camera.h"

namespace vstmr {

	class Window;
	class Renderer : public Component
	{
	public:
		Renderer() = default;

	public:
		void Init();

	public:
		void Render();
		//NOTE: REMOVE LATER
		vstmr::PerspectiveCamera* camera;

	private:
		std::shared_ptr<Shaders> m_shaders;
	};

}
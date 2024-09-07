#pragma once

#include <string>
#include <memory>

#include "Shaders.h"
#include "BufferSetStore.h"

#include "ECS/SceneContainer.h"
#include "camera/Camera.h"
#include "componentProcessors/MeshRendererProcessor.h"

namespace vstmr {

	class Window;
	class Renderer : public SceneContainer
	{
	public:
		Renderer() = default;
		
	public:
		void Init();
		void Render();

	public:
		//Camera can chill here for now
		vstmr::PerspectiveCamera camera{ glm::radians(90.0f), 1, 0.001, 1000 };

	private:
		MeshRendererProcessor m_mesh_renderer;
		
	};

}
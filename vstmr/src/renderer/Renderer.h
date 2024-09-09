#pragma once

#include <string>
#include <memory>

#include "Shaders.h"

#include "ECS/SceneContainer.h"
#include "camera/Camera.h"
#include "ECSSystems/MeshRendererSystem.h"

namespace vstmr {

	class Window;
	class Renderer : public SceneContainer
	{
	public:
		Renderer() = default;
		
	public:
		void Init();
		void Render();

	private:
		MeshRendererSystem m_mesh_renderer;
		
	};

}
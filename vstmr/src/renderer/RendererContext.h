#include "ECS/SceneContainer.h"

namespace vstmr {

	class RendererContext : public SceneContainer
	{
	public:
		RendererContext() = default;

	public:
		template<class T>
		T& CreateSceneContainer()
		{
			AddComponent<std::decay_t<T>>();
		}

	};

}
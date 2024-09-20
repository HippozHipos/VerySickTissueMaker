#pragma once

#include <imgui.h>
#include "Src/UI/Imgui/imgui_impl_glfw.h"
#include "Src/UI/Imgui/imgui_impl_opengl3.h"

#include "Src/Renderer/Renderer.h"
#include "Src/Renderer/Texture.h"
#include "Src/Window/MainPlatformWindow.h"
#include "Src/Window/Window.h"
#include "Src/Main/Application.h"

#include "Src/ECS/SceneContainer.h"
#include "Src/ECS/SceneObject.h"
#include "Src/ECS/Behaviour/BehaviourObject.h"
#include "Src/ECS/Behaviour/BehaviourSceneObject.h"

#include "Src/Renderer/Material.h"
#include "Src/Renderer/Mesh.h"
#include "Src/Renderer/MeshRenderer.h"
#include "Src/Renderer/Quad.h"

#include "Src/Renderer/PointLight.h"

#include "Src/ResourceLoader/ModelLoader.h"

#include "Src/Diagnostics/Logger.h"

#include "Src/ResourceLoader/ResourcePathHandler.h"
#include "Src/ResourceLoader/TextureManager.h"
		
#include "Src/Renderer/Camera.h"
#include "Src/Renderer/Graphics.h"
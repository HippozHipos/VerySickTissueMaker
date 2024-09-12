#pragma once

#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "src/renderer/Renderer.h"
#include "src/renderer/Texture.h"
#include "src/window/Window.h"
#include "src/Main/Application.h"

#include "src/ECS/SceneContainer.h"
#include "src/ECS/SceneObject.h"
#include "src/ECS/BehaviouralSceneObject.h"

#include "src/renderer/Material.h"
#include "src/renderer/MeshComponent.h"
#include "src/renderer/MeshRenderer.h"
#include "src/renderer/Quad.h"

#include "src/renderer/PointLight.h"

#include "src/ResourceLoader/MeshLoader.h"

#include "renderer/Camera.h"
#include "renderer/Graphics.h"

#include "src/Main/EntryPoint.h"
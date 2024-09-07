#pragma once

#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "src/renderer/Renderer.h"
#include "src/renderer/Texture.h"
#include "src/renderer/camera/Camera.h"
#include "src/window/Window.h"
#include "src/vstmr/Application.h"

#include "src/ECS/SceneContainer.h"

#include "src/renderer/Material.h"
#include "src/renderer/MeshComponent.h"
#include "src/renderer/SceneObject.h"
#include "src/renderer/MeshRenderer.h"
#include "src/renderer/Quad.h"

#include "src/renderer/PointLight.h"

#include "src/ResourceLoader/MeshLoader.h"

#include "src/vstmr/EntryPoint.h"
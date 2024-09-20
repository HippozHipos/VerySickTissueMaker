#include "EditorMainSceneViewPannel.h"
#include "EditorFonts.h"
#include "UtilWidgets.h"

namespace bee {

    bee::EditorMainSceneViewPannel::EditorMainSceneViewPannel(std::unordered_map<std::string, be::SceneObject>& editorSceneObjects) :
        m_editor_scene_objects{ editorSceneObjects }
    {
    }

    void EditorMainSceneViewPannel::UI()
    {
        if (ImGui::Begin(m_name))
        {
            ShowPointLights();
            DrawSeperator(1);
            ShowMeshRenderer();
            DrawSeperator(1);
        }
        ImGui::End();
    }

    void EditorMainSceneViewPannel::ShowMeshRenderer()
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        if (ImGui::TreeNode("Scene Objects"))
        { 
            ImGui::PopFont();
            for (auto& pair : m_editor_scene_objects)
            {
                if (ImGui::TreeNode(pair.second.Get<ObjectData>().name.c_str()))
                {
                    ShowMeshTransform(pair.second.Get<be::Transform>());
                    if (be::MeshRenderer* renderer = pair.second.TryGet<be::MeshRenderer>())
                    {
                        ImGui::PushFont(EditorFonts::roboto_bold);
                        if (ImGui::TreeNode("MeshRenderer"))
                        {
                            ImGui::PopFont();
                            ShowMeshRendererDrawModeDropdown(*renderer);
                            ImGui::PushFont(EditorFonts::roboto_bold);
                            if (ImGui::TreeNode("Material"))
                            {
                                ImGui::PopFont();
                                ShowMaterialColor(renderer->material);
                                ImGui::TreePop();
                            }
                            else
                            {
                                ImGui::PopFont();
                            }
                            ShowRendererModelButton(*renderer);
                            ShowMeshRendererStats(*renderer);
                            ImGui::Separator();
                            ImGui::TreePop();
                        }
                        else
                        {
                            ImGui::PopFont();
                        }
                    }
                    ShowComponentAdder(pair.second);
                    ImGui::Separator();
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        else
        {
            ImGui::PopFont();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshTransform(be::Transform& transform)
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        if (ImGui::TreeNode("Transform"))
        {
            ImGui::PopFont();
            ImGui::DragFloat3("Position", &transform.position[0], 0.2f);
            ImGui::DragFloat3("Rotation", &transform.rotation[0]);
            ImGui::DragFloat3("Scale", &transform.scale[0]);
            ImGui::TreePop();
        }
        else
        {
            ImGui::PopFont();
        }
        ImGui::Separator();
    }

    void EditorMainSceneViewPannel::ShowMaterialColor(be::Material& material)
    {
        ImGui::ColorPicker3("Color", &material.color[0]);
    }

    void EditorMainSceneViewPannel::ShowComponentAdder(be::SceneObject& object)
    {
        if (ImGui::Button("Add Component")) 
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup")) 
        {
            if (ImGui::MenuItem("MeshRenderer")) 
            {
                if (!object.Has<be::MeshRenderer>()) 
                {
                    object.Add<be::MeshRenderer>();
                }
            }
            ImGui::EndPopup();
        }
    }

    void EditorMainSceneViewPannel::ShowRendererModelButton(be::MeshRenderer& renderer)
    {

        ImGui::Button(renderer.model_name.c_str());
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MODEL_FILE_PATH"))
            {
                renderer.model_path = static_cast<char*>(payload->Data);
                renderer.model_name = std::filesystem::path{ renderer.model_path }.filename().string();
                be::ModelLoader::Load(renderer.model_path.c_str(), renderer);
                for (int i = 0; i < renderer.meshes.size(); i++)
                {
                    renderer.meshes[i].SetupMesh();
                }
            }
            ImGui::EndDragDropTarget();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshRendererStats(be::MeshRenderer& renderer)
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        if (ImGui::TreeNode("Stats"))
        {
            ImGui::PopFont();
            ImGui::Text("Vertices: %d", renderer.GetVertexCount());
            ImGui::Text("Indices: %d", renderer.GetIndexCount());
            ImGui::Text("Triangles drawn: %d", renderer.GetIndexCount() / 3);
            ImGui::TreePop();
        }
        else
        {
            ImGui::PopFont();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshRendererDrawModeDropdown(be::MeshRenderer& renderer)
    {
        static std::array<const char*, 3> drawModes{ "Points", "Lines", "Fill" };
        static std::array<int, 3> glModes{ GL_POINT, GL_LINE, GL_FILL };

        int currentModeIndex = 0;
        for (int i = 0; i < glModes.size(); ++i)
        {
            if (renderer.draw_mode == glModes[i])
            {
                currentModeIndex = i;
                break;
            }
        }

        if (ImGui::Combo("Draw Mode", &currentModeIndex, drawModes.data(), drawModes.size()))
        {
            renderer.draw_mode = glModes[currentModeIndex];
        }
    }

    void EditorMainSceneViewPannel::ShowPointLights()
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        if (ImGui::TreeNode("Lights"))
        {
            ImGui::PopFont();
            for (auto& pair : m_editor_scene_objects)
            {
                if (be::PointLight* light = pair.second.TryGet<be::PointLight>())
                {
                    if (ImGui::TreeNode(light->GetParent<ObjectData>().name.c_str()))
                    {
                        ImGui::ColorPicker3("Color", &light->color[0]);
                        ImGui::TreePop();
                    }
                }
            }
            ImGui::TreePop();
        }
        else
        {
            ImGui::PopFont();
        }
    }

}

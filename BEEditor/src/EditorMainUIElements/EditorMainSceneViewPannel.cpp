#include "EditorMainSceneViewPannel.h"

namespace bee {

    bee::EditorMainSceneViewPannel::EditorMainSceneViewPannel(std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& editorSceneObjects) :
        m_editor_scene_objects{ editorSceneObjects }
    {
    }

    void EditorMainSceneViewPannel::UI()
    {
        if (ImGui::Begin(m_name))
        {
            for (auto& pair : m_editor_scene_objects)
            {
                EditorSceneObject& object = pair.second.first;
                ShowMeshRenderer(object);
            }
            ImGui::End();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshRenderer(EditorSceneObject& object)
    {
        if (ImGui::TreeNode(object.GetName()))
        {
            be::MeshRenderer& renderer = object.Get<be::MeshRenderer>();
            ShowMeshTransform(object.Get<be::Transform>());
            ShowMeshRendererDrawModeDropdown(renderer);

            ImGui::TreePop();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshTransform(be::Transform& transform)
    {
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", &transform.position[0]);
        ImGui::DragFloat3("Rotation", &transform.rotation[0]);
        ImGui::DragFloat3("Scale", &transform.scale[0]);
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

        ImGui::Text("Draw Mode");
        if (ImGui::Combo("Draw Mode", &currentModeIndex, drawModes.data(), drawModes.size()))
        {
            renderer.draw_mode = glModes[currentModeIndex];
        }
    }


}

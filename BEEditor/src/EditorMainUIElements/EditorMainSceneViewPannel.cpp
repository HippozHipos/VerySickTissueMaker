#include "EditorMainSceneViewPannel.h"
#include "EditorFonts.h"

namespace bee {

    bee::EditorMainSceneViewPannel::EditorMainSceneViewPannel(std::unordered_map<std::string, EditorSceneObject>& editorSceneObjects) :
        m_editor_scene_objects{ editorSceneObjects }
    {
    }

    void EditorMainSceneViewPannel::UI()
    {
        if (ImGui::Begin(m_name))
        {
            for (auto& pair : m_editor_scene_objects)
            {
                EditorSceneObject& object = pair.second;
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
            ShowMaterialColor(renderer.material);

            ImGui::TreePop();
        }
    }

    void EditorMainSceneViewPannel::ShowMeshTransform(be::Transform& transform)
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        ImGui::Text("Transform");
        ImGui::PopFont();
        ImGui::DragFloat3("Position", &transform.position[0], 0.2f);
        ImGui::DragFloat3("Rotation", &transform.rotation[0]);
        ImGui::DragFloat3("Scale", &transform.scale[0]);
    }

    void EditorMainSceneViewPannel::ShowMaterialColor(be::Material& material)
    {
        ImGui::PushFont(EditorFonts::roboto_bold);
        ImGui::Text("Material");
        ImGui::PopFont();
        ImGui::DragFloat3("Color", &material.color[0], 0.001f, 0.0f, 1.0f);
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

        ImGui::PushFont(EditorFonts::roboto_bold);
        ImGui::Text("Draw Mode");
        ImGui::PopFont();
        if (ImGui::Combo("Draw Mode", &currentModeIndex, drawModes.data(), drawModes.size()))
        {
            renderer.draw_mode = glModes[currentModeIndex];
        }
    }
}

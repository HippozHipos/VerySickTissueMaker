#pragma once

#include <BECore/BECore.h>
#include  "EditorSceneObject.h"

namespace bee {

    class EditorMainSceneViewPannel : public be::BehaviourObject<EditorMainSceneViewPannel>
    {
    public:
        EditorMainSceneViewPannel(std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& editorSceneObjects);

    public:
        void UI();

    private:
        void ShowMeshRenderer(EditorSceneObject& object);
        void ShowMeshTransform(be::Transform& transform);
        void ShowMaterialColor(be::Material& material);
        void ShowMeshRendererDrawModeDropdown(be::MeshRenderer& renderer);

    private:
        std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& m_editor_scene_objects;
        const char* m_name = "Scene View";
    };

}
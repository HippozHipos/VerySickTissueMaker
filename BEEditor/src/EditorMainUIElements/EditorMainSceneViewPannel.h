#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorMainSceneViewPannel : public be::BehaviourObject<EditorMainSceneViewPannel>
    {
    public:
        EditorMainSceneViewPannel(std::unordered_map<std::string, be::SceneObject>& editorSceneObjects);

    public:
        void UI();

    private:
        //mesh, material, renderer stuff
        void ShowMeshRenderer();
        void ShowMeshTransform(be::Transform& transform);
        void ShowMaterialColor(be::Material& material);
        void ShowComponentAdder(be::SceneObject& object);
        void ShowRendererModelButton(be::MeshRenderer& renderer);
        void ShowMeshRendererStats(be::MeshRenderer& renderer);
        void ShowMeshRendererDrawModeDropdown(be::MeshRenderer& renderer);

        //light stuff
        void ShowPointLights();

    private:
        std::unordered_map<std::string, be::SceneObject>& m_editor_scene_objects;
        const char* m_name = "Scene View";
    };

}
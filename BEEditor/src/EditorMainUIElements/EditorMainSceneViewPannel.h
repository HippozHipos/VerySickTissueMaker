#pragma once

#include <BECore/BECore.h>
#include  "SceneObjectHolder.h"

namespace bee {

    class EditorMainSceneViewPannel : public be::BehaviourObject<EditorMainSceneViewPannel>
    {
    public:
        EditorMainSceneViewPannel(std::unordered_map<std::string, SceneObjectHolder>& editorSceneObjects);

    public:
        void UI();

    private:
        //mesh, material, renderer stuff
        void ShowMeshRenderer();
        void ShowMeshTransform(be::Transform& transform);
        void ShowMaterialColor(be::Material& material);
        void ShowComponentAdder(SceneObjectHolder& object);
        void ShowRendererModelButton(be::MeshRenderer& renderer);
        void ShowMeshRendererStats(be::MeshRenderer& renderer);
        void ShowMeshRendererDrawModeDropdown(be::MeshRenderer& renderer);

        //light stuff
        void ShowPointLights();

    private:
        std::unordered_map<std::string, SceneObjectHolder>& m_editor_scene_objects;
        const char* m_name = "Scene View";
    };

}
#pragma once

#include <BECore/BECore.h>
#include "EditorSceneObject.h"

namespace bee {

    class EditorMainViewportWindow : public be::BehaviourSceneObject<EditorMainViewportWindow>
    {
    public:
        EditorMainViewportWindow();

    public:
        void Update();
        void ProcessKeyboardMovement();
        void ProcessMouseMovement();
        void UI();

    private:
        void AcceptDragDropPayloadFromResourcePannel();

    private:
        const char* m_name = "Scene";
        std::vector<EditorSceneObject> m_editor_scene_objects;
    };

}
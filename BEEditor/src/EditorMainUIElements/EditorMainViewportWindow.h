#pragma once

#include <BECore/BECore.h>
#include "EditorSceneObject.h"

namespace bee {

    class EditorMainViewportWindow : public be::BehaviourSceneObject<EditorMainViewportWindow>
    {
    public:
        EditorMainViewportWindow(std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& editorSceneObjects);

    public:
        void Update();
        void ProcessKeyboardMovement();
        void ProcessMouseMovement();
        void UI();

    private:
        void AcceptDragDropPayloadFromResourcePannel();

    private:
        const char* m_name = "Scene";
        std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& m_editor_scene_objects;
    };

}
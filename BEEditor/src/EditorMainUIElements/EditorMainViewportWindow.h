#pragma once

#include <BECore/BECore.h>
#include "EditorSceneObject.h"

namespace bee {

    class EditorMainViewportWindow : public be::BehaviourSceneObject<EditorMainViewportWindow>
    {
    public:
        EditorMainViewportWindow(std::unordered_map<std::string, EditorSceneObject>& m_objects_map);

    public:
        void Update();
        void ProcessKeyboardMovement();
        void ProcessMouseMovement();
        void UI();

    private:
        void AddEditorSceneObject(const char* name);

        std::pair<char*, std::string> AcceptDragDropPayloadFromResourcePannel(const char* payloadid);
        void AcceptDragDropPointLightPayload();

    private:
        const char* m_name = "Scene";
        std::unordered_map<std::string, EditorSceneObject>& m_editor_scene_objects;
    };

}
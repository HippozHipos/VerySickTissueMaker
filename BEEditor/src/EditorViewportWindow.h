#pragma once

#include <BECore/BECore.h>
#include "SceneObjectHolder.h"

namespace bee {

    class EditorMainViewportWindow : public be::BehaviourSceneObject<EditorMainViewportWindow>
    {
    public:
        EditorMainViewportWindow(std::unordered_map<std::string, SceneObject>& m_objects_map);

    public:
        void Update();
        void ProcessKeyboardMovement();
        void ProcessMouseMovement();
        void UI();

    private:
        void AddEditorSceneObject(const char* name);
        void AddPointLight(const char* name);
        std::pair<char*, std::string> AcceptDragDropPayloadFromResourcePannel(const char* payloadid);
        char* AcceptDragDropPayloadFromCreationPannel(const char* payloadid, const char* title, const char* msg);

        void AcceptFromCreationPannel();

    private:
        const char* m_name = "Scene";
        std::unordered_map<std::string, SceneObject>& m_editor_scene_objects;
    };

}
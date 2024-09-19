#pragma once

#include "EditorMainTitleBar.h"
#include "EditorMainViewportWindow.h"
#include "EditorMainAssetsPannel.h"
#include "EditorMainSceneViewPannel.h"
#include "EditorMainCreationPannel.h"
#include "NotificationManager.h"

namespace bee {

    class EditorMainUIElements : public be::BehaviourObject<EditorMainUIElements>
    {
    public:
        void UI()
        {
            NotificationManager::ShowNotifications();
        }

    public:
        EditorMainAssetsPannel assets_pannel;
        EditorMainTitleBar title_bar;
        EditorMainViewportWindow viewport_window{ m_objects_map };
        EditorMainSceneViewPannel scene_view_panne{ m_objects_map };
        EditorMainCreationPannel creation_pannel;

    private:
        std::unordered_map<std::string, EditorSceneObject> m_objects_map;
    };
}
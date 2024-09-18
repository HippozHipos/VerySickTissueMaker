#pragma once

#include "EditorMainTitleBar.h"
#include "EditorMainViewportWindow.h"
#include "EditorMainAssetsPannel.h"
#include "EditorMainSceneViewPannel.h"

namespace bee {

    class EditorMainUIElements 
    {
    public:
        EditorMainAssetsPannel assets_pannel;
        EditorMainTitleBar title_bar;
        EditorMainViewportWindow viewport_window{ m_objects_map };
        EditorMainSceneViewPannel scene_view_panne{ m_objects_map };

    private:
        std::unordered_map<std::string, std::pair<EditorSceneObject, int>> m_objects_map;
    };
}
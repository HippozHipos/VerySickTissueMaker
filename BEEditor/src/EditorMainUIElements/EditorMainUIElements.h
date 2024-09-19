#pragma once

#include "EditorMainTitleBar.h"
#include "EditorMainViewportWindow.h"
#include "EditorMainAssetsPannel.h"
#include "EditorMainSceneViewPannel.h"
#include "EditorMainCreationPannel.h"

namespace bee {

    class EditorMainUIElements 
    {
    public:
        void UI()
        {
            
        }

    public:
        EditorMainAssetsPannel assets_pannel;
        EditorMainTitleBar title_bar;
        EditorMainViewportWindow viewport_window{ m_objects_map };
        EditorMainSceneViewPannel scene_view_panne{ m_objects_map };
        EditorMainCreationPannel creation_pannel;

    private:
        std::unordered_map<std::string, SceneObjectHolder> m_objects_map;
    };
}
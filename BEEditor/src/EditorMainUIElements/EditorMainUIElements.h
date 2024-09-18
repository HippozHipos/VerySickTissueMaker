#pragma once

#include "EditorMainTitleBar.h"
#include "EditorMainViewportWindow.h"
#include "EditorMainAssetsPannel.h"

namespace bee {

    class EditorMainUIElements 
    {
    public:
        EditorMainAssetsPannel assets_pannel;
        EditorMainTitleBar title_bar;
        EditorMainViewportWindow viewport_window;
    };
}
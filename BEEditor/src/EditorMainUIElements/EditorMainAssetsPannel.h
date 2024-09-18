#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorMainAssetsPannel : public be::BehaviourSceneObject<EditorMainAssetsPannel>
    {
    public:
        EditorMainAssetsPannel();

    public:
        void UI();

    private:
        void ShowResourcePannelFileExploer();

    private:
        std::string m_root_resource_path; 
        std::string m_dragged_file;
        std::vector<std::pair<std::string, std::string>> m_explorer_found_files;
        std::filesystem::path m_current_path;
        const char* m_name = "Resource Browser";
    };

}
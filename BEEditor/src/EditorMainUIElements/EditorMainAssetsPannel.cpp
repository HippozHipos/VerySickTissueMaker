#include "EditorMainAssetsPannel.h"

namespace bee {

	EditorMainAssetsPannel::EditorMainAssetsPannel()
	{
		m_root_resource_path = be::ResourcePathHandler::GetResourcePath();
		m_current_path = m_root_resource_path;
	}

	void EditorMainAssetsPannel::UI()
	{
		if (ImGui::Begin(m_name))
		{
			ShowResourcePannelFileExploer();
			ImGui::End();
		}
	}

    void EditorMainAssetsPannel::ShowResourcePannelFileExploer()
    {
        if (m_current_path != m_root_resource_path)
        {
            if (ImGui::Button(".."))
            {
                m_current_path = m_current_path.parent_path();
            }
        }

        // Show all the folders together in the same line
        m_explorer_found_files.clear();
        for (auto& path : std::filesystem::directory_iterator(m_current_path))
        {
            if (path.is_directory())
            {
                // Render folder buttons
                ImGui::SameLine();
                if (ImGui::Button(path.path().filename().string().c_str(), ImVec2{ 100, 100 }))
                {
                    m_current_path = path.path();
                }
            }
            else
            {
                m_explorer_found_files.push_back(std::pair<std::string, std::string>(
                    path.path().filename().string(),
                    path.path().string()));
            }
        }

        // Show all the files after the folders
        for (auto& pair : m_explorer_found_files)
        {
            ImGui::Indent(30.0f);
            ImGui::Button(pair.first.c_str());
            ImGui::Unindent(30.0f);

            if (ImGui::BeginDragDropSource())
            {
                m_dragged_file = pair.second;
                ImGui::SetDragDropPayload("FILE_PATH", m_dragged_file.c_str(), m_dragged_file.size() + 1);
                ImGui::Text(pair.first.c_str());
                ImGui::EndDragDropSource();
            }
        }
    }

}

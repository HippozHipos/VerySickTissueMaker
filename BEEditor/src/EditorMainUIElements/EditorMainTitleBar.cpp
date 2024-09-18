#include "EditorMainTitleBar.h"

namespace bee {

	void EditorMainTitleBar::UI()
    {
        ImGui::ShowDemoWindow();
        ImGui::ShowMetricsWindow();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

}
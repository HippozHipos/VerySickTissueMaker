#include "UtilWidgets.h"
#include <imgui.h>

namespace bee {

	char* BEETextInputPopup(const char* title, const char* msg)
	{
        static bool openPopup = false;
        if (openPopup)
        {
            ImGui::OpenPopup(title);
            openPopup = false;
        }

        if (ImGui::BeginPopupModal(title, nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char input[32] = "";
            ImGui::Text("Object name");
            ImGui::InputText("##textInput", input, IM_ARRAYSIZE(input));
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
                return input;
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
	}

    void DrawSeperator(int thickness)
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p1 = ImGui::GetCursorScreenPos();  
        ImVec2 p2 = ImVec2(p1.x + ImGui::GetContentRegionAvail().x, p1.y);  
        draw_list->AddLine(p1, p2, IM_COL32(255, 255, 255, 100), thickness);
    }

}

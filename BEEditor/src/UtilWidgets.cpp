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

}

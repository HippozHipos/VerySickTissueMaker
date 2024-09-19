#include <ImGui.h>
#include "EditorMainCreationPannel.h"

namespace bee {

	void EditorMainCreationPannel::UI()
	{
		if (ImGui::Begin(m_name))
		{
			ShowPointLight();
			ImGui::End();
		}
	}

	void EditorMainCreationPannel::ShowPointLight()
	{
		ImGui::Button("Point Light", ImVec2{ ImGui::GetContentRegionAvail().x , 50 });
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("POINT_LIGHT", nullptr, 0);
			ImGui::Text("Point Light");
			ImGui::EndDragDropSource();
		}
	}

}

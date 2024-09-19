#include <ImGui.h>
#include "EditorMainCreationPannel.h"

namespace bee {

	void EditorMainCreationPannel::UI()
	{
		if (ImGui::Begin(m_name))
		{
			ShowSceneObject();
			ShowPointLight();
			ImGui::End();
		}
	}

	void EditorMainCreationPannel::ShowSceneObject()
	{
		ImGui::Button("SceneObject", ImVec2{ ImGui::GetContentRegionAvail().x , 50 });
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("CREATE_SCENE_OBJECT", nullptr, 0);
			ImGui::Text("Scene Object");
			ImGui::EndDragDropSource();
		}
	}

	void EditorMainCreationPannel::ShowPointLight()
	{
		ImGui::Button("Point Light", ImVec2{ ImGui::GetContentRegionAvail().x , 50 });
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("CREATE_POINT_LIGHT", nullptr, 0);
			ImGui::Text("Point Light");
			ImGui::EndDragDropSource();
		}
	}

}

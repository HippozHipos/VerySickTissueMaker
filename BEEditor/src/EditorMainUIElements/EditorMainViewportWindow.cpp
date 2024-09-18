#include "EditorMainViewportWindow.h"
#include <imgui_internal.h>

namespace bee {

	EditorMainViewportWindow::EditorMainViewportWindow(std::unordered_map<std::string, std::pair<EditorSceneObject, int>>& editorSceneObjects) :
        m_editor_scene_objects{ editorSceneObjects }
	{
		GetRenderer().CreateViewport(m_name);
        be::Camera& cam = Add<be::Camera>(glm::radians(90.0f), 1, 0.01f, 10000.0f);
        cam.target_viewport = m_name;
	}

    void EditorMainViewportWindow::Update()
    {
        Get<be::Camera>().Update();
    }

	void EditorMainViewportWindow::UI()
	{
        ImGuiWindowFlags flags = GetRenderer().GetViewport(m_name)->second.GetFlags();
        if (ImGui::Begin(m_name, nullptr, flags))
        {
            float aspect = ImGui::GetWindowWidth() / ImGui::GetWindowHeight();
            Get<be::Camera>().RecalculateProjectionMatrix(glm::radians(90.0f), aspect, 0.01f, 10000.0f);
            AcceptDragDropPayloadFromResourcePannel();

            ProcessKeyboardMovement();
            ProcessMouseMovement();
            ImGui::End();
        }
	}

	void EditorMainViewportWindow::AcceptDragDropPayloadFromResourcePannel()
	{
        //imgui drag drop doesnt work with Begin() and End() since they are
        //only used for setting up the actual window, like window size, so
        //it needs something that can register the drop, in this case InvisibleButton.
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
        ImVec2 dropAreaSize = ImGui::GetContentRegionAvail();
        ImVec2 dropAreaEndPos = ImVec2(cursorPos.x + dropAreaSize.x, cursorPos.y + dropAreaSize.y);
        ImGui::ItemAdd({ cursorPos , dropAreaEndPos }, window->GetID("DropArea"));

        if (ImGui::IsItemHovered() && ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_PATH"))
            {
                std::string path{ static_cast<char*>(payload->Data) };
                auto it = m_editor_scene_objects.find(path.c_str());
                if (it == m_editor_scene_objects.end()) //add new with 1 count if doesnt exist
                {
                    std::string filename = std::filesystem::path{ path }.filename().string();
                    std::string withoutExtention = filename.substr(0, filename.find_last_of("."));
                    std::pair<EditorSceneObject, int> objectWithCount{ EditorSceneObject{ withoutExtention.c_str(), path.c_str()}, 1};
                    m_editor_scene_objects.insert(
                        std::pair<std::string, std::pair<EditorSceneObject, int>>{ path.c_str(), objectWithCount }
                    );
                }
                else
                {
                    //cant add duplicates for now
                }
            }
            ImGui::EndDragDropTarget();
        }
	}

    void EditorMainViewportWindow::ProcessKeyboardMovement()
    {
        be::Camera& camera = Get<be::Camera>();
        ImGuiIO& io = ImGui::GetIO();

        if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
            //NOTE: This locking only works if editor is fully inside the main main window.
            //need to find a solution that makes it work with imgui
            GetWindow().DisableCursor();
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            float velocity = camera.movement_speed * GetTimer().GetDeltaTime();
            if (ImGui::IsKeyDown(ImGuiKey_W))
                camera.position += camera.Forward() * velocity;
            if (ImGui::IsKeyDown(ImGuiKey_S))
                camera.position -= camera.Forward() * velocity;
            if (ImGui::IsKeyDown(ImGuiKey_A))
                camera.position -= camera.Right() * velocity;
            if (ImGui::IsKeyDown(ImGuiKey_D))
                camera.position += camera.Right() * velocity;
            if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
                camera.position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
            if (ImGui::IsKeyDown(ImGuiKey_Space))
                camera.position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
        }
        else
        {
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
            GetWindow().DefaultCursor();
        }
    }

    void EditorMainViewportWindow::ProcessMouseMovement()
    {
        be::Camera& camera = Get<be::Camera>();
        ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
        if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            camera.rotation.z += mouseDelta.x * camera.mouse_sensitivity;
            camera.rotation.y += -mouseDelta.y * camera.mouse_sensitivity;
            camera.rotation.y = std::min(89.0f, std::max(camera.rotation.y, -89.0f));
        }
    }

}

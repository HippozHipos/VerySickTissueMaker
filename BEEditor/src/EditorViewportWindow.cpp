#include "EditorViewportWindow.h"
#include <imgui_internal.h>
#include "UtilWidgets.h"
#include "NotificationManager.h"

namespace bee {

	EditorMainViewportWindow::EditorMainViewportWindow(std::unordered_map<std::string, SceneObject>& editorSceneObjects) :
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
            
            AcceptFromCreationPannel();
                
            ProcessKeyboardMovement();
        }
        ImGui::End();
	}

    void EditorMainViewportWindow::AddEditorSceneObject(const char* name)
    {
         auto it = m_editor_scene_objects.find(std::string{ name });
         if (it == m_editor_scene_objects.end())
         {
             SceneObject object{};
             object.Get<ObjectData>().name = name;
             m_editor_scene_objects.insert(
                 std::pair<std::string, SceneObject>{ name, object }
             );
             std::string msg = std::string{ "New object " } + name + " added";
             BELOG_CD_INFO(msg.c_str());
         }
         else
         {
             //cant add duplicates for now
         }
    }

    void EditorMainViewportWindow::AddPointLight(const char* name)
    {
        auto it = m_editor_scene_objects.find(std::string{ name });
        if (it == m_editor_scene_objects.end())
        {
            SceneObject object{};
            object.Get<ObjectData>().name = name;
            object.Add<be::PointLight>();
            m_editor_scene_objects.insert(
                std::pair<std::string, SceneObject>{ name, object }
            );
            std::string msg = std::string{ "New point light " } + name + " added";
            BELOG_CD_INFO(msg.c_str());
        }
        else
        {
            //cant add duplicates for now
        }
    }

    std::pair<char*, std::string> EditorMainViewportWindow::AcceptDragDropPayloadFromResourcePannel(const char* payloadid)
	{
        static bool openPopup = false;  
        static std::string path;
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadid))
            {
                openPopup = true;
                path = static_cast<char*>(payload->Data);
            }
            ImGui::EndDragDropTarget();
        }

        if (openPopup)
        {
            ImGui::OpenPopup("Create new scene object");
            openPopup = false;  
        }

        if (ImGui::BeginPopupModal("Create new scene object", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char name[32] = "";
            ImGui::Text("Object name");
            ImGui::InputText("##textInput", name, IM_ARRAYSIZE(name));
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return { name, path };
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }          
        return { nullptr, {} };
	}

    char* EditorMainViewportWindow::AcceptDragDropPayloadFromCreationPannel(const char* payloadid, const char* title, const char* msg)
    {
        static bool openPopup = false;
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadid))
            {
                openPopup = true;
            }
            ImGui::EndDragDropTarget();
        }

        if (openPopup)
        {
            ImGui::OpenPopup(title);
            openPopup = false;
        }

        if (ImGui::BeginPopupModal(title, nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            static char name[32] = "";
            ImGui::Text(msg);
            ImGui::InputText("##textInput", name, IM_ARRAYSIZE(name));
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return name;
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        return nullptr;
    }

    void EditorMainViewportWindow::AcceptFromCreationPannel()
    {
        char* scname = AcceptDragDropPayloadFromCreationPannel("CREATE_SCENE_OBJECT", "Create New Scene Object", "Enter Scene Object Name");
        if (scname) AddEditorSceneObject(scname);

        char* plname = AcceptDragDropPayloadFromCreationPannel("CREATE_POINT_LIGHT", "Create New Point Light", "Enter Point Light Name");
        if (plname) AddPointLight(plname);
    }

    void EditorMainViewportWindow::ProcessKeyboardMovement()
    {
        be::Camera& camera = Get<be::Camera>();
        ImGuiIO& io = ImGui::GetIO();
        static double pressposcaturex = 0;
        static double pressposcaturey = 0;
        static bool needpressposcature = true;
        // Get the viewport of the hovered window
        ImGuiViewport* viewport = ImGui::GetWindowViewport();
        if (viewport)
        {
            GLFWwindow* glfwWindow = (GLFWwindow*)viewport->PlatformHandle;
            if (glfwWindow)
            {
                if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Right))
                {
                    if (needpressposcature)
                    {
                        needpressposcature = false;
                        glfwGetCursorPos(glfwWindow, &pressposcaturex, &pressposcaturey);
                    }
                    // Set the mouse cursor to None
                    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
                    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                    // Get the current mouse position
                    double mouseX, mouseY;
                    glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);

                    // Set the cursor position to the center
                    glfwSetCursorPos(glfwWindow, pressposcaturex, pressposcaturey);

                    // Calculate mouse delta
                    float deltaX = static_cast<float>(mouseX - pressposcaturex);
                    float deltaY = static_cast<float>(mouseY - pressposcaturey);

                    // Update camera rotation based on mouse delta
                    camera.rotation.z += deltaX * camera.mouse_sensitivity;
                    camera.rotation.y -= deltaY * camera.mouse_sensitivity;
                    camera.rotation.y = std::clamp(camera.rotation.y, -89.0f, 89.0f);

                    // Camera movement logic
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
                    needpressposcature = true;
                    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
                }
            }
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

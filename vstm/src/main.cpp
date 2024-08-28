#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class Application : public vstmr::Application
    {
    public:
        void Start() override
        {            
        }

        void Update(float deltaTime) override
        {

            if (m_window.MouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
            {
                m_window.DisableCursor();
               
                vstmr::PerspectiveCamera& camera = m_window.GetViewport().GetCamera();
                camera.ProcessKeyboardMovement(deltaTime,
                    m_window.KeyHeld(GLFW_KEY_W), m_window.KeyHeld(GLFW_KEY_S),
                    m_window.KeyHeld(GLFW_KEY_A), m_window.KeyHeld(GLFW_KEY_D),
                    m_window.KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window.KeyHeld(GLFW_KEY_SPACE));

                camera.ProcessMouseMovement(m_window.GetMouseChangeX(), m_window.GetMouseChangeY());
            }
            else
            {
                m_window.DefaultCursor();
            }
        }

        void ImGui(ImGuiIO& io) override
        {
            ImGui::Begin("Hello, world!");
            if (ImGui::Button("Hello world"))
            {
                VSTM_CD_LOGINFO("Button pressed");
            }
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
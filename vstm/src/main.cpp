#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class Application : public vstmr::Application
    {
    public:
        void Start() override
        {            
            vstmr::MeshRenderer meshRenderer;
            m_renderer.camera = &camera;
        }

        void Update(float deltaTime) override
        {
            m_window.ClearColor(m_background[0], m_background[1], m_background[2], m_background[3]);
            
            if (m_window.KeyPressed(GLFW_KEY_W))
            {
                VSTM_CD_LOGINFO("HELLLO");
            }

            if (m_window.MouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
            {
                m_window.DisableCursor();
               
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
            ImGui::ColorPicker4("Background color", m_background);
            ImGui::End();
        }

    private:
        float m_background[4];
        vstmr::PerspectiveCamera camera = vstmr::PerspectiveCamera{ 90, 1, 0.001, 1000 };
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
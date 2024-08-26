#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class Application : public vstmr::Application
    {
    public:
        void Update(float deltaTime) override
        {
            // Keyboard input
            m_renderer.GetActiveCamera().ProcessKeyboardMovement(deltaTime,
                m_window.KeyHeld(GLFW_KEY_W), m_window.KeyHeld(GLFW_KEY_S),
                m_window.KeyHeld(GLFW_KEY_A), m_window.KeyHeld(GLFW_KEY_D),
                m_window.KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window.KeyHeld(GLFW_KEY_SPACE));

            m_renderer.GetActiveCamera().ProcessMouseMovement(m_window.GetMouseChangeX(), m_window.GetMouseChangeY());
            // Reset the cursor to the centre of the screen
            m_window.DisableCursor();
        }
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
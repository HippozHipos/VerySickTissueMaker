#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class Layer1 : public vstmr::Layer
    {
    public:
        void Start()
        {
            m_window->DisableCursor();
            AddViewport(100, 100, 100, 100);
        }

        void Update(float deltaTime) override
        {
            // Keyboard input
            m_camera.ProcessKeyboardMovement(deltaTime,
                m_window->KeyHeld(GLFW_KEY_W), m_window->KeyHeld(GLFW_KEY_S),
                m_window->KeyHeld(GLFW_KEY_A), m_window->KeyHeld(GLFW_KEY_D),
                m_window->KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window->KeyHeld(GLFW_KEY_SPACE));

            m_camera.ProcessMouseMovement(m_window->GetMouseChangeX(), m_window->GetMouseChangeY());
        }
    };

    class Layer2 : public vstmr::Layer
    {
    public:
        void Start()
        {
            m_window->DisableCursor();
            AddViewport(250, 50, 200, 200);
        }

        void Update(float deltaTime) override
        {
            // Keyboard input
            m_camera.ProcessKeyboardMovement(deltaTime,
                m_window->KeyHeld(GLFW_KEY_W), m_window->KeyHeld(GLFW_KEY_S),
                m_window->KeyHeld(GLFW_KEY_A), m_window->KeyHeld(GLFW_KEY_D),
                m_window->KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window->KeyHeld(GLFW_KEY_SPACE));

            m_camera.ProcessMouseMovement(m_window->GetMouseChangeX(), m_window->GetMouseChangeY());
        }
    };

    class Application : public vstmr::Application
    {
    public:
        void Start() override
        {
            m_window.GetLayerStack()->PushBackLayer(&layer1);
            m_window.GetLayerStack()->PushBackLayer(&layer2);
        }

    private:
        Layer1 layer1{};
        Layer2 layer2{};
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
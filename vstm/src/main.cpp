#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class Layer1 : public vstmr::Layer
    {
    public:
        void Start()
        {
            m_window->DisableCursor();
            AddViewport(0, 0, 100, 100);
            m_viewports[0]->r = 0.0f;
            m_viewports[0]->g = 1.0f;
            m_viewports[0]->b = 0.0f;
            m_viewports[0]->a = 1.0f;
        }

        void Update(float deltaTime) override
        {
            for (int i = 0; i < m_viewports.size(); i++)
            {
                vstmr::PerspectiveCamera& camera = m_viewports[i]->GetCamera();
                camera.ProcessKeyboardMovement(deltaTime,
                    m_window->KeyHeld(GLFW_KEY_W), m_window->KeyHeld(GLFW_KEY_S),
                    m_window->KeyHeld(GLFW_KEY_A), m_window->KeyHeld(GLFW_KEY_D),
                    m_window->KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window->KeyHeld(GLFW_KEY_SPACE));

                camera.ProcessMouseMovement(m_window->GetMouseChangeX(), m_window->GetMouseChangeY());
            }
        }
    };

    class Layer2 : public vstmr::Layer
    {
    public:
        void Start()
        {
            m_window->DisableCursor();
            AddViewport(300, 150, 100, 300);
            AddViewport(150, 200, 50, 50);
        }

        void Update(float deltaTime) override
        {
            for (int i = 0; i < m_viewports.size(); i++)
            {
                vstmr::PerspectiveCamera& camera = m_viewports[i]->GetCamera();
                camera.ProcessKeyboardMovement(deltaTime,
                    m_window->KeyHeld(GLFW_KEY_W), m_window->KeyHeld(GLFW_KEY_S),
                    m_window->KeyHeld(GLFW_KEY_A), m_window->KeyHeld(GLFW_KEY_D),
                    m_window->KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window->KeyHeld(GLFW_KEY_SPACE));

                camera.ProcessMouseMovement(m_window->GetMouseChangeX(), m_window->GetMouseChangeY());
            }
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
#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class UkeleleRenderer : public vstmr::Behaviour
    {
    public:
        UkeleleRenderer()
        {
            vstmr::MeshRenderer& meshRenderer = AddComponent<vstmr::MeshRenderer>();
            vstmr::MeshComponent& mesh = meshRenderer.GetComponent<vstmr::MeshComponent>();
            vstmr::MeshLoader::Load("../../../../vstmr/assets/models/Ukulele.obj", mesh);
            mesh.SetupMesh();
        }
    };

    class Application : public vstmr::Application
    {
    public:
        void Start() override
        {            
            m_root_container.AddComponent<UkeleleRenderer>();
        }

        void Update(float deltaTime) override
        {
            m_window.ClearColor(m_background[0], m_background[1], m_background[2], m_background[3]);

            if (m_window.MouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
            {
                m_window.DisableCursor();
               
                m_renderer.camera.ProcessKeyboardMovement(deltaTime,
                    m_window.KeyHeld(GLFW_KEY_W), m_window.KeyHeld(GLFW_KEY_S),
                    m_window.KeyHeld(GLFW_KEY_A), m_window.KeyHeld(GLFW_KEY_D),
                    m_window.KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window.KeyHeld(GLFW_KEY_SPACE));

                m_renderer.camera.ProcessMouseMovement(m_window.GetMouseChangeX(), m_window.GetMouseChangeY());
            }
            else
            {
                m_window.DefaultCursor();
            }
            m_renderer.camera.UpdateVectors();
        }

        void ImGui(ImGuiIO& io) override
        {
            ImGui::Begin("Hello, world!");
            ImGui::ColorPicker4("Background color", m_background);
            ImGui::End();
        }

    private:
        float m_background[4];
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
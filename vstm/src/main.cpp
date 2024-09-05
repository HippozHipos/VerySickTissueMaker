#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class UkeleleRenderer : public vstmr::Behaviour
    {
    public:
        UkeleleRenderer()
        {
            vstmr::MeshRenderer& meshRenderer = AddComponent<vstmr::MeshRenderer>();
            meshRenderer.GetComponent<vstmr::Material>().color = { 1.0f, 0.0f, 0.0f };
            vstmr::VectorComponent<vstmr::MeshComponent>& meshes = meshRenderer.GetComponent<vstmr::VectorComponent<vstmr::MeshComponent>>();
            vstmr::MeshLoader::Load("../../../../vstmr/assets/models/lowpoly.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
            {
                mesh.SetupMesh();
            }
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

            UkeleleRenderer& ukulele = m_root_container.GetComponent<UkeleleRenderer>();
            vstmr::MeshRenderer& meshRenderer = ukulele.GetComponent<vstmr::MeshRenderer>();
            meshRenderer.GetComponent<vstmr::Material>().color = color;
        }

        void ImGui(ImGuiIO& io) override
        {
            ImGui::Begin("Background");
            ImGui::ColorPicker4("Background color", m_background);
            ImGui::End();

            ImGui::Begin("Ukulele");
            ImGui::ColorPicker4("Ukulele color", &color[0]);
            ImGui::End();
        }

    private:
        float m_background[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
        glm::vec3 color = { 0.4f, 1.0f, 0.1f };
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
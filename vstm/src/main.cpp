#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class LowploySceneRenderer : public vstmr::SceneObject
    {
    public:
        LowploySceneRenderer()
        {
            vstmr::Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            vstmr::MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            meshRenderer.Get<vstmr::Material>().color = { 1.0f, 1.0f, 0.0f };
            vstmr::VectorComponent<vstmr::MeshComponent>& meshes = meshRenderer.Get<vstmr::VectorComponent<vstmr::MeshComponent>>();
            vstmr::MeshLoader::Load("../../../../vstmr/assets/models/lowpoly.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
            {
                mesh.SetupMesh();
            }
        }
    };

    class Light : public vstmr::BehaviouralSceneObject<Light>
    {
    public:
        Light()
        {
            vstmr::Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0.0f, 20, 5 };
            transform.rotation = { 0, 0, 0 };
            transform.scale = { 0.05f, 0.05f, 0.05f };
            vstmr::PointLight& light = Add<vstmr::PointLight>();
            vstmr::MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            color = &light.color;
            vstmr::VectorComponent<vstmr::MeshComponent>& meshes = meshRenderer.Get<vstmr::VectorComponent<vstmr::MeshComponent>>();
            vstmr::MeshLoader::Load("../../../../vstmr/assets/models/cube.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
            {
                mesh.SetupMesh();
            }
        }

    public:
        void Start()
        {
            VSTM_CD_LOGINFO("Hello");
        }

        void Update()
        {

        }

        void End()
        {

        }

        /*void Update(vstmr::Window& window, float deltaTime, vstmr::PerspectiveCamera& camera)
        {
            vstmr::Transform& transform = Get<vstmr::Transform>();
            if (window.KeyHeld(GLFW_KEY_T))
                transform.position.y += 5 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_F))
                transform.position.x += 5 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_H))
                transform.position.x -= 5 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_G))
                transform.position.y -= 5 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_R))
                transform.position.z -= 5 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_Y))
                transform.position.z += 5 * deltaTime;

            if (window.KeyHeld(GLFW_KEY_Z))
                transform.rotation.x += 20 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_X))
                transform.rotation.y += 20 * deltaTime;
            if (window.KeyHeld(GLFW_KEY_C))
                transform.rotation.z += 20 * deltaTime;

        }*/

        void UI()
        {
            ImGui::Begin("Light Color w");
            ImGui::ColorPicker4("Light Color", &color->r);
            ImGui::End();
        }

    private:
        glm::vec3* color;
    };

    class Application : public vstmr::Application
    {
    public:
        void Start() override
        {            
            LowploySceneRenderer lcs{};
            
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
            //light.Update(m_window, deltaTime, m_renderer.camera);
            m_renderer.camera.UpdateVectors();
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
        Light light{};
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
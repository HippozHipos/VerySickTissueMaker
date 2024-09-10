#include <iostream>
#include <vstmr/vstmr.h>

using namespace vstmr;

namespace vstm {

    class Character : public BehaviouralSceneObject<Character>
    {
    public:
        void Update()
        {
            //Quick dirty back because its stored in application container
            Camera& camera = ECS::registry.view<Camera>().get<Camera>((entt::entity)0);


            Keyboard& key = GetKeyboard();
            Mouse& mouse = GetMouse();
            Window& window = GetWindow();

            if (mouse.ButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
            {
                window.DisableCursor();

                camera.ProcessKeyboardMovement(GetTimer().GetDeltaTime(),
                    key.Held(GLFW_KEY_W), key.Held(GLFW_KEY_S),
                    key.Held(GLFW_KEY_A), key.Held(GLFW_KEY_D),
                    key.Held(GLFW_KEY_LEFT_CONTROL), key.Held(GLFW_KEY_SPACE)
                );

                camera.ProcessMouseMovement(mouse.GetChangeX(), mouse.GetChangeY());
            }
            else
            {
                window.DefaultCursor();
            }
            camera.UpdateVectors();
        }

        void UI()
        {
            Camera& camera = ECS::registry.view<Camera>().get<Camera>((entt::entity)0);
            ImGui::Begin("Twin turbo, 12800HP, Twin exhaust, NOS infused feet.");
            ImGui::DragFloat("Scale", &camera.MovementSpeed, 0.1f); 
            ImGui::End();
        }
    };

    class Chineseplan051classdestoryer051 : public BehaviouralSceneObject<Chineseplan051classdestoryer051>
    {
    public:
        Chineseplan051classdestoryer051(TextureManager& tm) :
            m_tm{ tm }
        {
        }

    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            MeshLoader::Load("../../../../vstmr/assets/models/ukulele.obj", meshRenderer, m_tm);
            meshRenderer.material.textures[0] = Texture{
                "C:\\Dev\\vstmr\\VerySickTissueMaker\\vstmr\\assets\\images\\wood.png"
                };
            for (vstmr::MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Cube Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().material.color[0]);
            ImGui::Checkbox("Wireframode mode", &Get<MeshRenderer>().wireframe_mode);
            ImGui::DragFloat3("Position", &Get<vstmr::Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<vstmr::Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<vstmr::Transform>().scale[0], 0.1f);
            ImGui::End();
        }

    private:
        TextureManager& m_tm;
    };

    class Wolf : public BehaviouralSceneObject<Wolf>
    {
    public:
        Wolf(TextureManager& tm) :
            m_tm{ tm }
        {
        }

    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            MeshLoader::Load("../../../../vstmr/assets/models/33-fbx/fbx/wolf.fbx", meshRenderer, m_tm);
            for (vstmr::MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Wolf Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().material.color[0]);
            ImGui::Checkbox("Wireframode mode", &Get<MeshRenderer>().wireframe_mode);
            ImGui::DragFloat3("Position", &Get<vstmr::Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<vstmr::Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<vstmr::Transform>().scale[0], 0.1f);
            ImGui::End();
        }

    private:
        TextureManager& m_tm;
    };

    class Light : public BehaviouralSceneObject<Light>
    {
    public:
        Light(TextureManager& tm) :
            m_tm{ tm }
        {
        }


    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            transform.scale = { 0.1f, 0.1f, 0.1f };
            Add<vstmr::PointLight>();
            MeshRenderer& meshRenderer = Add<MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            MeshLoader::Load("../../../../vstmr/assets/models/cube.obj", meshRenderer, m_tm);

            for (vstmr::MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Light Color");
            ImGui::ColorPicker3("Light color picker", &Get<PointLight>().color[0]);
            ImGui::DragFloat3("Light Position", &Get<vstmr::Transform>().position[0], 0.1f);
            ImGui::End();
        }

        void Update()
        {
            Get<MeshRenderer>().material.color = Get<PointLight>().color;
        }
    private:
        TextureManager& m_tm;

    };

    class Application : public vstmr::Application
    {
    public:
        Application()
        {
            tm.Init();
        }
 
        TextureManager tm;
        Character character{};
        Chineseplan051classdestoryer051 chinesedestroyer{ tm };
        Wolf wolf{ tm };
        Light light1{ tm };
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
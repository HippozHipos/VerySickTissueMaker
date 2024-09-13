#include <iostream>
#include <vstmr/vstmr.h>

using namespace be;

namespace vstm {

    class Editor : public BehaviouralSceneObject<Editor>
    {
    public:
        void Start()
        {
            GetRenderer().CreateViewport("Editor1");
        }
    };

    class Character1 : public BehaviouralSceneObject<Character1>
    {
    public:
        void Start()
        {
            Camera& camera = Add<Camera>(glm::radians(90.0f), 1, 0.001, 10000);
            camera.target_viewport = "Editor1";
        }

        void Update()
        {            
            Get<Camera>().Update();
        }

        void UI()
        {
            ImGui::Begin("Twin turbo, 12800HP, Twin exhaust, NOS infused feet.");
            ImGui::DragFloat("Scale", &Get<Camera>().movement_speed, 0.1f);
            ImGui::End();
            ProcessKeyboardMovement();
            ProcessMouseMovement();
        }

    private:
        void ProcessKeyboardMovement()
        {
            Camera& camera = Get<Camera>();
            Keyboard& key = GetKeyboard();
            Mouse& mouse = GetMouse();
            Window& window = GetWindow();
            if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
            {
                window.DisableCursor();
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
                window.DefaultCursor();
            }
        }

        void ProcessMouseMovement()
        {
            Camera& camera = Get<Camera>();
            Mouse& mouse = GetMouse();

            if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
            {
                camera.rotation.z += mouse.ChangeX() * camera.mouse_sensitivity;
                camera.rotation.y += mouse.ChangeY() * camera.mouse_sensitivity;
                camera.rotation.y = std::min(89.0f, std::max(camera.rotation.y, -89.0f));
            }
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
            Transform& transform = Get<Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            ModelLoader::Load("../../../../vstmr/assets/models/ukulele.obj", meshRenderer, m_tm);
            meshRenderer.material.textures[0] = Texture{
                "C:\\Dev\\vstmr\\VerySickTissueMaker\\vstmr\\assets\\images\\wood.png"
                };
            for (MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Cube Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().material.color[0]);
            ImGui::DragFloat3("Position", &Get<Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<Transform>().scale[0], 0.1f);
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
            Transform& transform = Get<Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            ModelLoader::Load("../../../../vstmr/assets/models/33-fbx/fbx/wolf.fbx", meshRenderer, m_tm);
            for (MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Wolf Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().material.color[0]);
            ImGui::DragFloat3("Position", &Get<Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<Transform>().scale[0], 0.1f);
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
            Transform& transform = Get<Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            transform.scale = { 0.1f, 0.1f, 0.1f };
            Add<PointLight>();
            MeshRenderer& meshRenderer = Add<MeshRenderer>();
            meshRenderer.material.color = { 1.0f, 1.0f, 0.0f };
            ModelLoader::Load("../../../../vstmr/assets/models/cube.obj", meshRenderer, m_tm);

            for (MeshComponent& mesh : meshRenderer.meshes)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Light Color");
            ImGui::ColorPicker3("Light color picker", &Get<PointLight>().color[0]);
            ImGui::DragFloat3("Light Position", &Get<Transform>().position[0], 0.1f);
            ImGui::End();
        }

        void Update()
        {
            Get<MeshRenderer>().material.color = Get<PointLight>().color;
        }
    private:
        TextureManager& m_tm;

    };

    class Application : public be::Application
    {
    public:
        Application()
        {
            tm.Init();
            config_flag = Application::ENABLE_VIEWPORTS;// | Application::SETUP_MAIN_WINDOW_AS_DOCKSPACE;
        }
 
        Editor editor{};
        TextureManager tm;
        Character1 character1{};
        Chineseplan051classdestoryer051 chinesedestroyer{ tm };
        Wolf wolf{ tm };
        Light light1{ tm };
    };

}

be::Application* be::CreateApplication()
{
    return new vstm::Application{};
}
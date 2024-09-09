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

            window.ClearColor(0.5, 0.5, 0.5, 1);

            if (mouse.ButtonHeld(GLFW_MOUSE_BUTTON_RIGHT))
            {
                window.DisableCursor();

                camera.ProcessKeyboardMovement(GetTimer().GetDeltaTime(),
                    key.Held(GLFW_KEY_W), key.Held(GLFW_KEY_S),
                    key.Held(GLFW_KEY_A), key.Held(GLFW_KEY_D),
                    key.Held(GLFW_KEY_LEFT_CONTROL), key.Held(GLFW_KEY_SPACE));

                camera.ProcessMouseMovement(mouse.GetChangeX(), mouse.GetChangeY());
            }
            else
            {
                window.DefaultCursor();
            }
            camera.UpdateVectors();
        }
    };

    class Cube : public BehaviouralSceneObject<Cube>
    {
    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            meshRenderer.Get<Material>().color = { 1.0f, 1.0f, 0.0f };
            VectorComponent<MeshComponent>& meshes = meshRenderer.Get<VectorComponent<MeshComponent>>();
            MeshLoader::Load("../../../../vstmr/assets/models/cube.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Cube Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().Get<Material>().color[0]);
            ImGui::Checkbox("Wireframode mode", &Get<MeshRenderer>().wireframe_mode);
            ImGui::DragFloat3("Position", &Get<vstmr::Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<vstmr::Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<vstmr::Transform>().scale[0], 0.1f);
            ImGui::End();
        }
    };

    class Ukulele : public BehaviouralSceneObject<Ukulele>
    {
    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            MeshRenderer& meshRenderer = Add<vstmr::MeshRenderer>();
            meshRenderer.Get<Material>().color = { 1.0f, 1.0f, 0.0f };
            VectorComponent<MeshComponent>& meshes = meshRenderer.Get<VectorComponent<MeshComponent>>();
            MeshLoader::Load("../../../../vstmr/assets/models/ukulele.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
            {
                mesh.SetupMesh();
            }
        }

        void UI()
        {
            ImGui::Begin("Ukulele Settings");
            ImGui::ColorPicker3("Light color picker", &Get<MeshRenderer>().Get<Material>().color[0]);
            ImGui::Checkbox("Wireframode mode", &Get<MeshRenderer>().wireframe_mode);
            ImGui::DragFloat3("Position", &Get<vstmr::Transform>().position[0], 0.1f);
            ImGui::DragFloat3("Rotation", &Get<vstmr::Transform>().rotation[0], 0.1f);
            ImGui::DragFloat3("Scale", &Get<vstmr::Transform>().scale[0], 0.1f);
            ImGui::End();
        }
    };

    class Light : public BehaviouralSceneObject<Light>
    {
    public:
        void Start()
        {
            Transform& transform = Get<vstmr::Transform>();
            transform.position = { 0, 0, 0 };
            transform.rotation = { 0, 0, 0 };
            transform.scale = { 0.1f, 0.1f, 0.1f };
            Add<vstmr::PointLight>();
            MeshRenderer& meshRenderer = Add<MeshRenderer>();
            meshRenderer.Get<Material>().color = { 1.0f, 1.0f, 0.0f };
            VectorComponent<MeshComponent>& meshes = meshRenderer.Get<VectorComponent<MeshComponent>>();
            MeshLoader::Load("../../../../vstmr/assets/models/cube.obj", meshes.vector);
            for (vstmr::MeshComponent& mesh : meshes.vector)
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
            Get<MeshRenderer>().Get<Material>().color = Get<PointLight>().color;
        }
    };

    class Application : public vstmr::Application
    {
    public:     
        Character character{};
        Cube scene{};
        Ukulele ukulele{};
        Light light1{};
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
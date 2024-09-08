#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class ThingInSceneWithBehaviour : public vstmr::BehaviouralSceneObject<ThingInSceneWithBehaviour>
    {
    public:
        void PreStart()
        {
            VSTM_CD_LOGINFO("Pre start from ThingInSceneWithBehaviour");
        }

        void End()
        {
            VSTM_CD_LOGINFO("End from ThingInSceneWithBehaviour");
        }

        void PostEnd()
        {
            VSTM_CD_LOGINFO("PostEnd from ThingInSceneWithBehaviour");
        }
       
    };

    class AnotherThingInSceneWithBehaviour : public vstmr::BehaviouralSceneObject<AnotherThingInSceneWithBehaviour>
    {
    public:
        void Update()
        {
            vstmr::Keyboard& keyboard = GetKeyboard();
            if (keyboard.Held(GLFW_KEY_W))
            {
                std::cout << "Ws in the chat\n";
            }

            vstmr::Mouse& mouse = GetMouse();
            if (mouse.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                std::cout << "Left clicks in the chat\n";
            }
        }

        void UI()
        {
            ImGui::Begin("Color window");
            ImGui::ColorPicker3("Pick", color);
            ImGui::End();
        }

        float color[3] = { 0.0f, 0.0f, 0.0f };
    };

    class Application : public vstmr::Application
    {
    public:
        Application()
        {
            ThingInSceneWithBehaviour thing{};
        }
        AnotherThingInSceneWithBehaviour anotherthing{};
    };

}

vstmr::Application* vstmr::CreateApplication()
{
    return new vstm::Application{};
}
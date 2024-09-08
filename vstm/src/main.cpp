#include <iostream>
#include <vstmr/vstmr.h>

namespace vstm {

    class ThingInSceneWithBehaviour : public vstmr::BehaviouralSceneObject<ThingInSceneWithBehaviour>
    {
    public:
        void PreStart()
        {
            VSTM_CD_LOGINFO("ThingInSceneWithBehaviour was created after AnotherThingInSceneWithBehaviour");
        }

        void UI()
        {
            ImGui::Begin("Color window");
            ImGui::ColorPicker3("Pick", color);
            ImGui::End();
        }
        float color[3] = { 0.0f, 0.0f, 0.0f };
    };

    class AnotherThingInSceneWithBehaviour : public vstmr::BehaviouralSceneObject<AnotherThingInSceneWithBehaviour>
    {
    public:
        void PreStart()
        {
            VSTM_CD_LOGINFO("Hello from AnotherThingInSceneWithBehaviour");
        }

        void End()
        {
            VSTM_CD_LOGINFO("Bye from AnotherThingInSceneWithBehaviour");
        }
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
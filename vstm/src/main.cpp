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

        void Start()
        {
            VSTM_CD_LOGINFO("Start from ThingInSceneWithBehaviour");
        }

        void End()
        {
            VSTM_CD_LOGINFO("End from ThingInSceneWithBehaviour");
        }

        void PostEnd()
        {
            VSTM_CD_LOGINFO("PostEnd from ThingInSceneWithBehaviour");
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
        void Start()
        {
            VSTM_CD_LOGINFO("Start from AnotherThingInSceneWithBehaviour");
        }

        void PreStart()
        {
            VSTM_CD_LOGINFO("PreStart from AnotherThingInSceneWithBehaviour");
        }

        void End()
        {
            VSTM_CD_LOGINFO("End from AnotherThingInSceneWithBehaviour");
        }

        void PostEnd()
        {
            VSTM_CD_LOGINFO("PostEnd from AnotherThingInSceneWithBehaviour");
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
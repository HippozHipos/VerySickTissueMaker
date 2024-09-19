#include <BECore/BECore.h>
#include <ImGui.h>
#include <Src/Main/EntryPoint.h>
#include "EditorMainUIElements/EditorMainUIElements.h"
#include "EditorFonts.h"

namespace bee{

    class EditorApplication : public be::Application
    {
    public:
        EditorApplication()
        {
            config_flag = be::Application::SETUP_MAIN_WINDOW_AS_DOCKSPACE | be::Application::ENABLE_VIEWPORTS;
        }
        
        void Init() override
        {
            EditorFonts::Init();
            ImGuiIO& io = ImGui::GetIO();
        }

        EditorMainUIElements ui_elements;
    };
    
}

be::Application* be::CreateApplication()
{
    return new bee::EditorApplication{};
}

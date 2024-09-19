#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorMainCreationPannel : public be::BehaviourObject<EditorMainCreationPannel>
    {
    public:
        void UI();

    private:
        void ShowSceneObject();
        void ShowPointLight();

    private:
        const char* m_name = "Creation Pannel";
    };
}
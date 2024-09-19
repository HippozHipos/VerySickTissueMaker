#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorSceneObject : public be::BehaviourSceneObject<EditorSceneObject>
    {
    public:
        EditorSceneObject(const char* name);

    public:
        const char* GetName() const;
        void SetName(const char* name);

    private:
        std::string m_name;
    };

}
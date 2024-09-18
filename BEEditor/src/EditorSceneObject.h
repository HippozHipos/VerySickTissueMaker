#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorSceneObject : public be::BehaviourSceneObject<EditorSceneObject>
    {
    public:
        EditorSceneObject(const char* name, const char* path);

    public:
        const char* GetName() const;
        const char* GetPath() const;

        void SetName(const char* name);

    private:
        std::string m_name;
        std::string m_path;
    };

}
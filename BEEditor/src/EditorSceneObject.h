#pragma once

#include <BECore/BECore.h>

namespace bee {

    class EditorSceneObject : public be::BehaviourSceneObject<EditorSceneObject>
    {
    public:
        EditorSceneObject(const char* path);
    };

}
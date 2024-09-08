#pragma once

#include "SceneObject.h"
#include "BehaviourManager.h"

namespace vstmr {

    //This is so we can share same instance of BehaviourManager 
    //across all the instances of BehaviouralSceneObject<T>
    //REMINDER: Needs to be moved somewhere else
    struct BehaviourManagerStore
    {   
        static BehaviourManager& GetBehaviourManager()
        {
            static BehaviourManager manager;
            return manager;
        }
    };

    template<typename Derived>
    class BehaviouralSceneObject : public SceneObject
    {
    public:
        virtual ~BehaviouralSceneObject()
        {
            BehaviourManagerStore::GetBehaviourManager().RemoveBehaviour<BehaviouralSceneObject, Derived>(*this);
        }

    public:
        BehaviouralSceneObject()
        {
            BehaviourManagerStore::GetBehaviourManager().AddBehaviour<BehaviouralSceneObject, Derived>(*this);
        } 
    };
}
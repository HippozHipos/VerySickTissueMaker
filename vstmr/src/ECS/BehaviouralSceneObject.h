#pragma once

#include "SceneObject.h"
#include "BehaviourManager.h"

namespace vstmr {

    //This is so we can share same instance of BehaviourManager 
    //across all the instances of BehaviouralSceneObject<T>
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
        BehaviouralSceneObject()
        {
            BehaviourManagerStore::GetBehaviourManager().AddBehaviour<BehaviouralSceneObject<Derived>>(*this);
        }

    public:
        void StartCaller() 
        {
            static_cast<Derived*>(this)->Start();
        }

        void UpdateCaller()
        {
            static_cast<Derived*>(this)->Update();
        }

        void UICaller()
        {
            static_cast<Derived*>(this)->UI();
        }

        void EndCaller()
        {
            static_cast<Derived*>(this)->End();
        }    
    };
}
#pragma once
#include "BehaviourManager.h"

namespace be {

    /*!
     * See Related BehaviourManager, BehaviouralSceneObject
     *
     * \class BehaviourManagerStore
     * \brief Singleton for BehaviourManager
     *
     * This class exists so that we can share the same instance of BehaviourManager
     * across all the instances of BehaviouralSceneObject<T>
     */
    struct BehaviourManagerStore
    {
        static BehaviourManager& GetBehaviourManager();
    };

}
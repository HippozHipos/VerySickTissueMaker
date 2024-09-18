#pragma once
#include "BehaviourManagerStore.h"
#include "Diagnostics/Logger.h"

namespace be {

    template<class Derived>
    class BehaviourProvider
    {
    public:
        /*!
         * \brief Registers the derived class objects behaviour with the behaviour manager.
         */
        BehaviourProvider()
        {
            BehaviourManagerStore::GetBehaviourManager().AddBehaviour<BehaviourProvider, Derived>(this);
        }

        /*!
         * \brief Registers the derived class objects behaviour with the behaviour manager.
         */
        BehaviourProvider(const BehaviourProvider& other)
        {
            BehaviourManagerStore::GetBehaviourManager().AddBehaviour<BehaviourProvider, Derived>(this);
        }

        /*!
        * \brief Unregisters the derived class objects behaviour from the behaviour manager.
        */
        virtual ~BehaviourProvider()
        {
            BehaviourManagerStore::GetBehaviourManager().RemoveBehaviour<BehaviourProvider, Derived>(this);
        }
    };

}
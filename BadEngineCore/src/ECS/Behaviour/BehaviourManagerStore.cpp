#include "BehaviourManagerStore.h"

namespace be {

    BehaviourManager& BehaviourManagerStore::GetBehaviourManager()
    {
        static BehaviourManager manager;
        return manager;
    }

}
#include "BehaviourManager.h"

namespace vstmr {

    void BehaviourManager::CallAllStart() const
    {
        for (auto& function : m_start_functions)
        {
            function();
        }
    }
}
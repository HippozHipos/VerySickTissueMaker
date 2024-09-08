#include "BehaviourManager.h"

namespace vstmr {

    void BehaviourManager::CallAllStartFunctions() const
    {
        for (auto& pair : m_start_functions)
        {
            pair.second();
        }
    }

    void BehaviourManager::CallAllUpdateFunctions() const
    {
        for (auto& pair : m_update_functions)
        {
            pair.second();
        }
    }

    void BehaviourManager::CallAllUIFunctions() const
    {
        for (auto& pair : m_gui_functions)
        {
            pair.second();
        }
    }
}
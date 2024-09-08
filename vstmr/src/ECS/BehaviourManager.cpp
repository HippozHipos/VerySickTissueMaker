#include "BehaviourManager.h"

namespace vstmr {

    void BehaviourManager::CallAllStartFunctions() const
    {
        for (auto& function : m_start_functions)
        {
            function();
        }
    }

    void BehaviourManager::CallAllUpdateFunctions() const
    {
        for (auto& function : m_update_functions)
        {
            function();
        }
    }

    void BehaviourManager::CallAllUIFunctions() const
    {
        for (auto& function : m_gui_functions)
        {
            function();
        }
    }

    void BehaviourManager::CallAllEndFunctions() const
    {
        for (auto& function : m_end_functions)
        {
            function();
        }
    }
}
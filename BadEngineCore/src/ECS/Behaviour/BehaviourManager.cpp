#include "BehaviourManager.h"

namespace be {

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
#include "NotificationManager.h"

namespace bee {

    std::vector<NotificationManager::Notification> NotificationManager::m_notifications{};

    void NotificationManager::AddNotification(const std::string& message, float displayTime)
    {
        m_notifications.push_back({ message, std::chrono::steady_clock::now(), displayTime });
    }

    void NotificationManager::ShowNotifications()
    {
        int i = 0;
        for (auto it = m_notifications.begin(); it != m_notifications.end();)
        {
            auto& notification = *it;
            auto elapsedTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - notification.startTime).count();

            if (elapsedTime >= notification.displayTime)
            {
                it = m_notifications.erase(it);
            }
            else
            {
                ImGui::SetNextWindowBgAlpha(0.7f);
                ImGui::SetNextWindowPos(ImVec2(10, 10 + i * 50), ImGuiCond_Always);

                ImGui::Begin("Notification", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize |
                    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove);
                ImGui::Text("%s", notification.message.c_str());
                ImGui::End();

                ++it;
                ++i;
            }
        }
    }

}

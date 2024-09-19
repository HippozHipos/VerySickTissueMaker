#pragma once
#include <BECore/BECore.h>

namespace bee {

    class NotificationManager
    {
    public:
        struct Notification
        {
            std::string message;
            std::chrono::steady_clock::time_point startTime;
            float displayTime; 
        };

        static void AddNotification(const std::string& message, float displayTime);
        static void ShowNotifications();

    private:
        static std::vector<Notification> m_notifications; 
    };

}
#pragma once

#include <type_traits>

#include <glfw/glfw3.h>

namespace vstmr {

    template<typename T = double, typename = std::remove_cv_t<std::is_arithmetic<T>>>
    class GenericTimer : public SceneContainer
    {
    public:
        GenericTimer() :
            m_last_frame_time(glfwGetTime()) {}

    public:
        void UpdateDeltaTime()
        {
            T currentTime = glfwGetTime();
            m_delta_time = currentTime - m_last_frame_time;
            m_last_frame_time = currentTime;
        }

        T GetDeltaTime()
        {
            return m_delta_time;
        }

    private:
        T m_delta_time = 0;
        T m_last_frame_time = 0;
    };

    using Timer = GenericTimer<float>;
}
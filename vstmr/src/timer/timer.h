#pragma once

#include <type_traits>

#include <glfw/glfw3.h>

template<typename T = double, typename = std::remove_cv_t<std::is_floating_point<T>>>
class Timer {
public:
    Timer() : m_last_frame_time(glfwGetTime()) {}

public:
    T getDeltaTime() 
    {
        T currentTime = glfwGetTime();
        T deltaTime = currentTime - m_last_frame_time;
        m_last_frame_time = currentTime;
        return deltaTime;
    }

private:
    T m_last_frame_time;
};
#pragma once
#include "pch.h"
#ifndef GLFW_INCLUDE_NONE 
    #define GLFW_INCLUDE_NONE 
#endif
#include <glfw/glfw3.h>
#include "ECS/SceneContainer.h"

namespace be {

    class Window : public SceneContainer
    {
    public:
        Window() = default;

    public:
        void DisableCursor();
        void DefaultCursor();
        void Update();

        void SetCurrentContext(GLFWwindow* context);

    private:
        bool m_needs_mouse_capture = true;
        bool m_is_cursor_disabled = false;
        float m_delta_x = 0;
        float m_delta_y = 0;
        double m_mouse_capture_pos_x = 0;
        double m_mouse_capture_pos_y = 0;

        GLFWwindow* m_current_context; //NOTE: EVENTALLY, WE WANT TO DETECT AND HANDLE IT THROUGH THIS CLASS
        GLFWwindow* m_last_context; //NOTE: EVENTALLY, WE WANT TO DETECT AND HANDLE IT THROUGH THIS CLASS
    };

}
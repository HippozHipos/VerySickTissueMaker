#include "Window.h"
#include <imgui.h>

namespace be {

    void Window::DisableCursor()
    {
        m_is_cursor_disabled = true;
        if (m_needs_mouse_capture)
        {
            m_needs_mouse_capture = false;
            glfwGetCursorPos(m_current_context, &m_mouse_capture_pos_x, &m_mouse_capture_pos_y);
        }

        glfwSetInputMode(m_current_context, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (ImGui::GetCurrentContext())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        }
    }

    void Window::DefaultCursor()
    {
        glfwSetInputMode(m_current_context, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (ImGui::GetCurrentContext())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        }
        m_needs_mouse_capture = true;
        m_is_cursor_disabled = false;
    }

    void Window::Update()
    {
        //do normal mouse delta calculation if cursor isnt disabled, if it 
        if (!m_is_cursor_disabled)
        {
            glfwGetCursorPos(m_current_context, &m_mouse_capture_pos_x, &m_mouse_capture_pos_y);
        }
        double currentx, currenty;
        glfwGetCursorPos(m_current_context, &currentx, &currenty);
        m_delta_x = static_cast<float>(currentx - m_mouse_capture_pos_x);
        m_delta_y = static_cast<float>(currenty - m_mouse_capture_pos_y);
    }

    void Window::SetCurrentContext(GLFWwindow* context)
    {
        if (m_current_context)
        {
            m_last_context = m_current_context;
        }
        else
        {
            m_last_context = context;
        }
        m_current_context = context;

        //we have changed context
        if (m_last_context != m_current_context)
        {
            m_needs_mouse_capture = true;
            m_is_cursor_disabled = false;
            m_delta_x = 0;
            m_delta_y = 0;
            m_mouse_capture_pos_x = 0;
            m_mouse_capture_pos_y = 0;
        }
    }
}
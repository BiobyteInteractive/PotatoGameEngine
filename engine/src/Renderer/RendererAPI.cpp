#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Core/Window.h"
#include "Color.h"
#include "RendererAPI.h"

namespace Engine {
    void RendererAPI::EndDrawing() {
        glfwSwapBuffers(this->m_Window->GetWindowHandle());
        glfwPollEvents();
    }

    void RendererAPI::ClearBackground(Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RendererAPI::SetContext(Window* window) {
        this->m_Window = window;
    }
}
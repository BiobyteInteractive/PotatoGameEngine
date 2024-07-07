#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Core/Window.h"
#include "../Color.h"
#include "OpenGL.h"

namespace Engine {
    void OpenGL::EndDrawing() {
        glfwSwapBuffers(this->m_Window->GetWindowHandle());
        glfwPollEvents();
    }

    void OpenGL::ClearBackground(Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGL::SetContext(Window* window) {
        this->m_Window = window;
    }

    void OpenGL::RenderImGuiDrawData() {}
}
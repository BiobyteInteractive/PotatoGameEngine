#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Core/Window.h"
#include "RendererAPI.h"

void RendererAPI::EndDrawing() {
    glfwSwapBuffers(this->m_Window->GetWindowHandle());
    glfwPollEvents();
}

void RendererAPI::ClearBackground(int r, int g, int b, int a) {
    glClearColor((float)r/255, (float)g/255, (float)b/255, (float)a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RendererAPI::SetContext(Window* window) {
    this->m_Window = window;
}
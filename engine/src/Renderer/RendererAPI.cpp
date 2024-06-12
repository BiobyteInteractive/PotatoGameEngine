#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RendererAPI.h"

void RendererAPI::EndDrawing(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void RendererAPI::ClearBackground(int r, int g, int b, int a) {
    glClearColor((float)r/255, (float)g/255, (float)b/255, (float)a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}
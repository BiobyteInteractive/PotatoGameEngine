#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

void processInput(GLFWwindow *window)
{
    //if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Renderer::BeginDrawing(GLFWwindow* window) {
    processInput(window);
}

void Renderer::EndDrawing(GLFWwindow* window) {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::ClearBackground(int r, int g, int b, int a) {
    glClearColor((float)r/255, (float)g/255, (float)b/255, (float)a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}
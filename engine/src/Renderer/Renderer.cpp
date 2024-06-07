#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include <iostream>

void processInput(GLFWwindow *window)
{
    //if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Renderer::Renderer(int screenWidth, int screenHeight, std::string windowTitle) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->m_Window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), NULL, NULL);
    if(this->m_Window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(this->m_Window);
    glfwSetFramebufferSizeCallback(this->m_Window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

Renderer::~Renderer() {
    glfwTerminate();
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
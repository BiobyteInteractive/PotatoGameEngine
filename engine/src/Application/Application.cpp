#include <float.h>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Application.h"
#include "../Renderer/Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Application::Application(int screenWidth, int screenHeight, std::string windowTitle) {
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

    this->m_Renderer = new Renderer();
}

Application::~Application() {
    glfwTerminate();
}

GLFWwindow* Application::GetWindow() {
    return this->m_Window;
}

void Application::Update(std::function<void()> update) {
    while(!this->WindowShouldClose()) {
        update();
    }
}

bool Application::WindowShouldClose() {
    return glfwWindowShouldClose(this->m_Window);
}

void Application::CloseWindow() {
    glfwSetWindowShouldClose(this->m_Window, 1);
}
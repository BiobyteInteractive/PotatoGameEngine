#include <float.h>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Application.h"
#include "../Renderer/Renderer.h"

Application::Application(int screenWidth, int screenHeight, std::string windowTitle) {
    this->m_Renderer = new Renderer(screenWidth, screenHeight, windowTitle);
}

Application::~Application() {
    glfwTerminate();
}

GLFWwindow* Application::GetWindow() {
    return this->m_Renderer->m_Window;
}

void Application::Update(std::function<void()> update) {
    while(!this->WindowShouldClose()) {
        update();
    }
}

bool Application::WindowShouldClose() {
    return glfwWindowShouldClose(this->m_Renderer->m_Window);
}

void Application::CloseApplication() {
    glfwSetWindowShouldClose(this->m_Renderer->m_Window, 1);
}
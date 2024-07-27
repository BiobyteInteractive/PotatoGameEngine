#include <float.h>
#include <functional>
#include <GLFW/glfw3.h>

#include <string>

#include "Application.h"
#include "../Renderer/Renderer.h"
#include "Window.h"

namespace Engine {
    Application::Application(int screenWidth, int screenHeight, std::string windowTitle) : m_Window(screenWidth, screenHeight, windowTitle) {
        this->m_Renderer = Renderer();
    }

    Application::~Application() {
        glfwTerminate();
    }

    GLFWwindow* Application::GetWindow() {
        return this->m_Window.GetWindowHandle();
    }

    void Application::Update(std::function<void()> update) {
        while(!this->WindowShouldClose()) {
            update();
        }
    }

    bool Application::WindowShouldClose() {
        return glfwWindowShouldClose(this->m_Window.GetWindowHandle());
    }

    void Application::CloseApplication() {
        glfwSetWindowShouldClose(this->m_Window.GetWindowHandle(), 1);
    }
}
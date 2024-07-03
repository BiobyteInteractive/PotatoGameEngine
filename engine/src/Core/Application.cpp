#include <float.h>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Application.h"
#include "../Renderer/RendererAPI.h"
#include "Window.h"

namespace Engine {
    Application::Application(int screenWidth, int screenHeight, std::string windowTitle) {
        this->m_Renderer = new RendererAPI();
        this->m_Window = new Window(screenWidth, screenHeight, windowTitle);
    }

    Application::~Application() {
        glfwTerminate();
    }

    GLFWwindow* Application::GetWindow() {
        return this->m_Window->GetWindowHandle();
    }

    void Application::Update(std::function<void()> update) {
        while(!this->WindowShouldClose()) {
            update();
        }
    }

    bool Application::WindowShouldClose() {
        return glfwWindowShouldClose(this->m_Window->GetWindowHandle());
    }

    void Application::CloseApplication() {
        glfwSetWindowShouldClose(this->m_Window->GetWindowHandle(), 1);
    }
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "../Debug/Logger.h"
#include "Window.h"

namespace Engine {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Window::Window(int screenWidth, int screenHeight, std::string windowTitle) {
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
            Logger::GetInstance().Error("Failed to create GLFW window");
            glfwTerminate();
        }
        
        glfwSetFramebufferSizeCallback(this->m_Window, framebuffer_size_callback);

        glfwMakeContextCurrent(this->m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Logger::GetInstance().Error("Failed to initialize GLAD");
        }
    }

    Window::~Window() {
        glfwTerminate();
    }

    GLFWwindow* Window::GetWindowHandle() {
        return this->m_Window;
    }
}
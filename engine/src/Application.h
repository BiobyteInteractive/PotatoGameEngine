#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

#include <string>

class DllExport Application {
    public:
        Application(int screenWidth, int screenHeight, std::string windowTitle);
        ~Application();

        GLFWwindow* GetWindow();
    private:
        void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        void ProcessInput();
    private:
        GLFWwindow* m_Window;
};

#endif
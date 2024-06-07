#pragma once
#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#define DllExport __declspec( dllexport )

#include "../Renderer/Renderer.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <string>

class DllExport Application {
    public:
        Application(int screenWidth, int screenHeight, std::string windowTitle);
        ~Application();

        void  Update(std::function<void()> update);
        GLFWwindow* GetWindow();
        bool WindowShouldClose();
        void CloseApplication();

        Renderer*   m_Renderer;
    private:
};

#endif
#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

#include "../Renderer/Renderer.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <string>

namespace Engine {
    class DllExport Application {
        public:
            Application(int screenWidth, int screenHeight, std::string windowTitle);
            ~Application();

            void  Update(std::function<void()> update);
            GLFWwindow* GetWindow();
            bool WindowShouldClose();
            void CloseApplication();
            void SetApplicationIcon();

        public:
            Renderer m_Renderer;
            Window m_Window;
    };
}
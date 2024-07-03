#pragma once

#include "../Renderer/RendererAPI.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <string>

#define DllExport __declspec( dllexport )

namespace Engine {
    class DllExport Application {
        public:
            Application(int screenWidth, int screenHeight, std::string windowTitle);
            ~Application();

            void  Update(std::function<void()> update);
            GLFWwindow* GetWindow();
            bool WindowShouldClose();
            void CloseApplication();

        public:
            RendererAPI* m_Renderer;
            Window*      m_Window;
    };
}
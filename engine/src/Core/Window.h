#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include <GLFW/glfw3.h>

#include <string>

namespace Engine {
    class DllExport Window {
        public:
            Window(int screenWidth, int screenHeight, std::string windowTitle);
            ~Window();
            GLFWwindow* GetWindowHandle();
        private:
            GLFWwindow* m_Window;
    };
}
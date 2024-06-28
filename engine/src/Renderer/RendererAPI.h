/*
    The RendererAPI should be an interface to be implemented by the different APIs (OpenGL, Vulkan, DirectX, Metal, WebGL, WebGPU).
*/

#pragma once

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

#include "../Core/Window.h"

class DllExport RendererAPI {
    public:
        enum class API {
            None   = 0,
            OpenGL = 1
        };
    public:
        ~RendererAPI() = default;

        void ClearBackground(int r, int g, int b, int a);
        void EndDrawing();

        void SetContext(Window* window);
    private:
        Window* m_Window;
    
    private:
        static API s_API;
};
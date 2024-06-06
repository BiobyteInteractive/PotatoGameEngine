#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

class DllExport Renderer {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void BeginDrawing(GLFWwindow* window);
        void ClearBackground(int r, int g, int b, int a);
        void EndDrawing(GLFWwindow* window);
    private:
};

#endif
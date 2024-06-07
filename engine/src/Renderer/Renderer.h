#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

#include <string>

class DllExport Renderer {
    public:
        Renderer(int screenWidth, int screenHeight, std::string windowTitle);
        ~Renderer();

        void BeginDrawing(GLFWwindow* window);
        void ClearBackground(int r, int g, int b, int a);
        void EndDrawing(GLFWwindow* window);
    public:
        GLFWwindow* m_Window;
};

#endif
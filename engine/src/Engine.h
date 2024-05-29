#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#define DllExport __declspec( dllexport )

#include <GLFW/glfw3.h>

DllExport int InitWindow(int screenWidth, int screenHeight, char* windowTitle);
DllExport bool WindowShouldClose();

DllExport void BeginDrawing();
DllExport void EndDrawing();

DllExport void ClearBackground(int r, int g, int b, int a);

DllExport GLFWwindow* GetWindow();

#endif
#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"
#include <Core/Application.h>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    Application* app = new Application(screenWidth, screenHeight, "Sandbox");
    GLFWwindow* window = app->GetWindow();
    Renderer* renderer = app->m_Renderer;

    while(!app->WindowShouldClose()) {
        renderer->BeginDrawing(window);

        renderer->ClearBackground(255, 0, 255, 255);

        renderer->EndDrawing(window);
    }

    return 0;
}
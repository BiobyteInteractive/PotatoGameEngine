#include "Renderer/RendererAPI.h"
#include <Core/Application.h>

using namespace Engine;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    Application* app = new Application(screenWidth, screenHeight, "Sandbox");
    RendererAPI* renderer = app->m_Renderer;

    renderer->SetContext(app->m_Window);

    while(!app->WindowShouldClose()) {

        renderer->ClearBackground(255, 0, 255, 255);

        renderer->EndDrawing();
    }

    return 0;
}
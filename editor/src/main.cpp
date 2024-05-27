#include <potato.h>

#include <GLFW/glfw3.h>

int main() {
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, (char*)"potato");

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(255, 0, 255, 255);
        EndDrawing();
    }
    
    return 0;
}
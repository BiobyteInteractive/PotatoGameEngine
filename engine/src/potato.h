#pragma once
#ifndef ENGINE_H
#define ENGINE_H

int InitWindow(int screenWidth, int screenHeight, char* windowTitle);
bool WindowShouldClose();

void BeginDrawing();
void EndDrawing();

void ClearBackground(int r, int g, int b, int a);

#endif
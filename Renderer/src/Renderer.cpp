#include "Renderer.h"

void gez::renderer::init(int screenWidth, int screenHeight, const char *title)
{
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

void gez::renderer::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
}
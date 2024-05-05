#pragma once
#include "raylib.h"

namespace gez
{
    namespace renderer
    {
        extern Camera2D camera;

        void init(int screenWidth, int screenHeight, const char *title);
        void run();
        void ClosestNode();
        void DrawNodes();
        void DrawHighways();
        void DrawFromAdjList();
    }
}
#pragma once
#include "raylib.h"

namespace gez
{
    namespace renderer
    {
        extern Camera2D camera;
        extern RenderTexture2D target;
        extern Vector4 *bounds;

        void init(int screenWidth, int screenHeight, const char *title);
        void run();
        void InitMapTexture();
        void DrawSelectedNodes();
        void DrawCursor();
        void DrawNodes();
        void DrawHighways();
        void DrawFromAdjList(int scale);
        void DrawDijkstra();
    }
}
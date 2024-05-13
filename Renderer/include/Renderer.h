#pragma once
#include "raylib.h"
#include <future>

namespace gez
{
    namespace renderer
    {
        extern Camera2D camera;
        extern RenderTexture2D target;
        extern Vector4 *bounds;
        extern int activeScene;
        extern std::future<void> isLoaded;
        extern int dataLoadStatus;

        void init(int screenWidth, int screenHeight, const char *title);
        void run();
        void InitMapTexture();
        void AsyncDataLoader();
        void DrawSelectedNodes();
        void DrawCursor();
        void DrawNodes();
        void DrawHighways();
        void DrawFromAdjList(int scale);
        void DrawDijkstra();
    }
}
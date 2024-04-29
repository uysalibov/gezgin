#pragma once
#include "raylib.h"

namespace gez
{
    namespace renderer
    {
        void init(int screenWidth, int screenHeight, const char *title);
        void run();
        void DrawHighways();
    }
}
#pragma once
#include "raylib.h"
#include "OSMJson.h"

namespace gez
{
    namespace renderer
    {
        extern Vector2 selectedPoints[2];
        extern int selectedPointsCount;

        void ProcessInput(Camera2D *camera);
    }
}
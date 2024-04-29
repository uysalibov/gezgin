#pragma once
#include <vector>
#include "nlohmann/json.hpp"
#include "raylib.h"
#include "KeyTypes.h"

namespace gez
{
    namespace fileparser
    {
        extern nlohmann::json jsonData;
        extern std::vector<Vector4> lines;
        extern std::vector<gez::HighwayType> highwayTypes;

        void ReadFile(const char *path);
        void PrintData();
        void ParseData();
        Vector4 *GetBounds();
        void StandardizeData();
        void ScaleData(int scaleFactorX, int scaleFactorY);
    }
}

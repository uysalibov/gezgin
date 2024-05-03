#pragma once
#include <vector>
#include <map>
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

        extern std::map<size_t, int> nodeMap;
        extern std::vector<Vector2> nodes;

        void ReadFile(const char *path);
        void PrintData();
        void AddNode(Vector2 node);
        void ParseData();
        Vector4 *GetBounds();
        size_t GetHash(Vector2 node);
        void StandardizeData();
        void ScaleData(int scaleFactor);
    }
}

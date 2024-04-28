#pragma once
#include "nlohmann/json.hpp"

namespace gez
{
    namespace fileparser
    {
        extern nlohmann::json jsonData;

        void ReadFile(const char *path);

        void PrintData();
    }
}

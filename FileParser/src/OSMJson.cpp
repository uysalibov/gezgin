#include "OSMJson.h"
#include <fstream>
#include <iostream>

nlohmann::json gez::fileparser::jsonData;

void gez::fileparser::ReadFile(const char *path)
{
    std::ifstream file(path);
    // check file is exists
    if (!file.is_open())
    {
        std::cerr << "File not found!" << std::endl;
        return;
    }

    jsonData = nlohmann::json::parse(file);
    file.close();
}

void gez::fileparser::PrintData()
{
    std::cout << jsonData.dump(4) << std::endl;
}
#include "OSMJson.h"
#include <fstream>
#include <iostream>

nlohmann::json gez::fileparser::jsonData;
std::vector<Vector4> gez::fileparser::lines;
std::vector<gez::HighwayType> gez::fileparser::highwayTypes;

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
    for (int i = 0, size = lines.size(); i < size; i++)
    {
        std::cout << lines[i].x << " " << lines[i].y << " - " << lines[i].z << " " << lines[i].w << std::endl;
    }
}

void gez::fileparser::ParseData()
{
    for (auto &element : jsonData["elements"])
    {
        if (element["type"] == "way")
        {
            Vector4 bounds = {element["bounds"]["minlat"], element["bounds"]["minlon"], element["bounds"]["maxlat"], element["bounds"]["maxlon"]};
            int size = element["geometry"].size();
            for (int i = 0; i < size - 1; i++)
            {
                Vector4 line;
                line.x = element["geometry"][i]["lat"].get<double>();
                line.y = element["geometry"][i]["lon"].get<double>();
                line.z = element["geometry"][i + 1]["lat"].get<double>();
                line.w = element["geometry"][i + 1]["lon"].get<double>();
                lines.push_back(line);
                highwayTypes.push_back(HighwayType::UNCLASSIFIED);
            }
        }
    }
}

Vector4 *gez::fileparser::GetBounds()
{
    Vector4 *bounds = new Vector4{lines[0].x, lines[0].y, lines[0].z, lines[0].w};
    for (int i = 1, size = lines.size(); i < size; i++)
    {
        Vector4 line = lines[i];
        if (line.x < bounds->x)
            bounds->x = line.x;
        if (line.y < bounds->y)
            bounds->y = line.y;
        if (line.z > bounds->z)
            bounds->z = line.z;
        if (line.w > bounds->w)
            bounds->w = line.w;
    }
    return bounds;
}

void gez::fileparser::StandardizeData()
{
    Vector4 *bounds = GetBounds();
    for (int i = 0, size = lines.size(); i < size; i++)
    {
        Vector4 line = lines[i];
        line.x = (line.x - bounds->x) / (bounds->z - bounds->x);
        line.y = (line.y - bounds->y) / (bounds->w - bounds->y);
        line.z = (line.z - bounds->x) / (bounds->z - bounds->x);
        line.w = (line.w - bounds->y) / (bounds->w - bounds->y);

        lines[i] = line;
    }
    std::cout << "Bounds: " << bounds->x << " " << bounds->y << " - " << bounds->z << " " << bounds->w << std::endl;
}

void gez::fileparser::ScaleData(int scaleFactorX, int scaleFactorY)
{
    for (int i = 0, size = lines.size(); i < size; i++)
    {
        Vector4 line = lines[i];
        line.x *= scaleFactorX;
        line.y *= scaleFactorY;
        line.z *= scaleFactorX;
        line.w *= scaleFactorY;

        lines[i] = line;
    }
}
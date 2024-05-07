#include "OSMJson.h"
#include "AdjList.h"
#include <fstream>
#include <iostream>

nlohmann::json gez::fileparser::jsonData;
std::vector<Vector4> gez::fileparser::lines;
std::vector<gez::HighwayType> gez::fileparser::highwayTypes;

std::map<size_t, int> gez::fileparser::nodeMap;
std::vector<Vector2> gez::fileparser::nodes;

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

void gez::fileparser::AddNode(Vector2 node)
{
    size_t hash = GetHash(node);
    // std::cout << "Hash: " << hash << std::endl;

    if (nodeMap.find(hash) == nodeMap.end())
    {
        nodes.push_back(node);
        nodeMap[hash] = nodes.size() - 1;
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
            for (int i = 0; i < size; i++)
            {
                Vector2 node;
                node.x = element["geometry"][i]["lat"].get<float>();
                node.y = element["geometry"][i]["lon"].get<float>();

                AddNode(node);
            }
        }
    }

    // add adjacencies
    TraceLog(LOG_INFO, "Initializing adjacency list");
    gez::AdjList::Init(nodes.size());
    TraceLog(LOG_INFO, "Adding adjacencies");
    for (auto &element : jsonData["elements"])
    {
        if (element["type"] == "way")
        {
            int size = element["geometry"].size();
            for (int i = 0; i < size - 1; i++)
            {
                Vector2 node1;
                node1.x = element["geometry"][i]["lat"].get<float>();
                node1.y = element["geometry"][i]["lon"].get<float>();

                Vector2 node2;
                node2.x = element["geometry"][i + 1]["lat"].get<float>();
                node2.y = element["geometry"][i + 1]["lon"].get<float>();

                int pos1 = nodeMap[GetHash(node1)];
                int pos2 = nodeMap[GetHash(node2)];

                gez::AdjList::AddAdj(pos1, pos2);
                gez::AdjList::AddAdj(pos2, pos1);
            }
        }
    }
    TraceLog(LOG_INFO, "Adjacencies added");
}

Vector4 *gez::fileparser::GetBounds()
{
    float max = std::numeric_limits<float>::max();
    float min = std::numeric_limits<float>::min();
    Vector4 *bounds = new Vector4{max, max, min, min};
    for (int i = 1, size = nodes.size(); i < size; i++)
    {
        if (nodes[i].x < bounds->x)
            bounds->x = nodes[i].x;
        if (nodes[i].y < bounds->y)
            bounds->y = nodes[i].y;
        if (nodes[i].x > bounds->z)
            bounds->z = nodes[i].x;
        if (nodes[i].y > bounds->w)
            bounds->w = nodes[i].y;
    }
    return bounds;
}

size_t gez::fileparser::GetHash(Vector2 node)
{
    std::string x = std::to_string(node.x);
    std::string y = std::to_string(node.y);
    return std::hash<std::string>{}(x + y);
}

void gez::fileparser::StandardizeData()
{
    Vector4 *bounds = GetBounds();
    for (int i = 0, size = nodes.size(); i < size; i++)
    {
        nodes[i].x = (nodes[i].x - bounds->x) / (bounds->z - bounds->x);
        nodes[i].y = (nodes[i].y - bounds->y) / (bounds->w - bounds->y);
    }
    std::cout << "Bounds: " << bounds->x << " " << bounds->y << " - " << bounds->z << " " << bounds->w << std::endl;
}

void gez::fileparser::ScaleData(int scaleFactor)
{
    for (int i = 0, size = nodes.size(); i < size; i++)
    {
        float temp = nodes[i].x;
        nodes[i].x = nodes[i].y * scaleFactor + 50;
        nodes[i].y = GetScreenHeight() - (temp * scaleFactor + 50);
        // nodes[i].x *= scaleFactor;
        // nodes[i].y *= scaleFactor;
    }
}
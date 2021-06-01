#pragma once

#include <string>
#include <vector>
#include "Vertex.h"

class Mesh
{
private:
    std::vector<Vertex> Data;

public:
    Mesh(const std::string& InFilePath);
    
    bool LoadMesh(const std::string& InFilePath);
    
    std::vector<Vertex>& GetVertex()
    {
        return Data;
    }
};

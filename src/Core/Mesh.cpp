#include "Mesh.h"

#include <iostream>
#include "Functions.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"

Mesh::Mesh(const std::string& InFilePath)
{
    LoadMesh(InFilePath);
}

bool Mesh::LoadMesh(const std::string& InFilePath)
{
    tinyobj::ObjReader reader;
    
    if (!reader.ParseFromFile(InFilePath))
    {
        if (!reader.Error().empty())
        {
            std::cout << "[ERR] : " << reader.Error() << std::endl;
            return false;
        }
    }
    
    if (!reader.Warning().empty())
    {
        std::cout << "[WARN] : " << reader.Warning() << std::endl;
    }
    
    const tinyobj::attrib_t& ObjAttrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>& ObjShapeArr = reader.GetShapes();
//    const std::vector<tinyobj::material_t>& ObjMatArr = reader.GetMaterials();
    
    for (auto& ObjShape : ObjShapeArr)
    {
        size_t IndexOffset = 0;
        for (auto numFV : ObjShape.mesh.num_face_vertices)
        {
            for (uint32 i = 0; i < numFV; i++)
            {
                auto& IndexInfo = ObjShape.mesh.indices[IndexOffset + i];
                
                tinyobj::real_t vx = ObjAttrib.vertices[3 * IndexInfo.vertex_index + 0];
                tinyobj::real_t vy = ObjAttrib.vertices[3 * IndexInfo.vertex_index + 1];
                tinyobj::real_t vz = ObjAttrib.vertices[3 * IndexInfo.vertex_index + 2];
                Vertex v(Vec3f(vx, vy, vz));
                
                if (IndexInfo.normal_index >= 0)
                {
                    tinyobj::real_t nx = ObjAttrib.normals[3 * IndexInfo.normal_index + 0];
                    tinyobj::real_t ny = ObjAttrib.normals[3 * IndexInfo.normal_index + 1];
                    tinyobj::real_t nz = ObjAttrib.normals[3 * IndexInfo.normal_index + 2];
                    v.Normal.X = nx;
                    v.Normal.Y = ny;
                    v.Normal.Z = nz;
                }
                
                if (IndexInfo.texcoord_index >= 0)
                {
                    tinyobj::real_t tx = ObjAttrib.texcoords[2 * IndexInfo.texcoord_index + 0];
                    tinyobj::real_t ty = ObjAttrib.texcoords[2 * IndexInfo.texcoord_index + 1];
                    v.UV.X = tx;
                    v.UV.Y = ty;
                }
                
                Data.push_back(v);
            }
            
            IndexOffset += numFV;
        }
    }
    
    return true;
}

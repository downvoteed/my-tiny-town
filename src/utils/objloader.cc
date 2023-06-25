#include "objloader.hh"

#include <tiny_obj_loader.h>

ObjLoader::ObjLoader(const std::string& filepath) 
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath.c_str()))
    {
        throw std::runtime_error(err);
    }

    for (const auto& shape : shapes) 
    {
        for (const auto& index : shape.mesh.indices) 
        {
            glm::vec3 vertex = 
            {
                attrib.vertices[3 * size_t(index.vertex_index) + 0],
                attrib.vertices[3 * size_t(index.vertex_index) + 1],
                attrib.vertices[3 * size_t(index.vertex_index) + 2]
            };
            this->vertices_.push_back(vertex);

            glm::vec2 texcoord = 
            {
                attrib.texcoords[2 * size_t(index.texcoord_index) + 0],
                attrib.texcoords[2 * size_t(index.texcoord_index) + 1]
            };
            this->texCoords_.push_back(texcoord);

            glm::vec3 normal =
            {
                attrib.normals[3 * size_t(index.normal_index) + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };
            this->normals_.push_back(normal);

            this->indices_.push_back(index.vertex_index);
        }
    }
}

std::vector<glm::vec3> ObjLoader::getVertices() const 
{
    this->vertices_
}

std::vector<glm::vec3> ObjLoader::getNormals() const 
{
    this->normals_;
}

std::vector<glm::vec2> ObjLoader::getTexCoords() const 
{
    return this->texCoords_
}

std::vector<unsigned int> ObjLoader::getIndices() const 
{
    return this->indices_;
}
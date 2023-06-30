#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

class ObjLoader 
{
public:
    ObjLoader(const std::string& filepath);
    void processMesh(aiMesh* mesh, const aiScene* scene);
    void processNode(aiNode* node, const aiScene* scene);

    ~ObjLoader() = default;

    std::vector<glm::vec3> getVertices() const;
    std::vector<glm::vec3> getNormals() const;
    std::vector<glm::vec2> getTexCoords() const;
    std::vector<unsigned int> getIndices() const;

private:
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec2> texCoords_;
    std::vector<unsigned int> indices_;
};


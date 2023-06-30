#include "objloader.hh"
#include <iostream>

void ObjLoader::processNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    // Then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void ObjLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        aiVector3D pos = mesh->mVertices[i];
        vertices_.push_back(glm::vec3(pos.x, pos.y, pos.z));

        if(mesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
        {
            aiVector3D UVW = mesh->mTextureCoords[0][i]; // assume each mesh only has one set of texture coords
            texCoords_.push_back(glm::vec2(UVW.x, UVW.y));
        }

        if(mesh->HasNormals())
        {
            aiVector3D n = mesh->mNormals[i];
            normals_.push_back(glm::vec3(n.x, n.y, n.z));
        }
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices_.push_back(face.mIndices[j]);
    }
}

ObjLoader::ObjLoader(const std::string& filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes
        | aiProcess_JoinIdenticalVertices);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

std::vector<glm::vec3> ObjLoader::getVertices() const
{
    return this->vertices_;
}

std::vector<glm::vec3> ObjLoader::getNormals() const
{
    return this->normals_;
}

std::vector<glm::vec2> ObjLoader::getTexCoords() const
{
    return this->texCoords_;
}

std::vector<unsigned int> ObjLoader::getIndices() const
{
    return this->indices_;
}

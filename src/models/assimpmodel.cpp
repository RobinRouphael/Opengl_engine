//
// Created by Robin on 11/03/2020.
//

#include "assimpmodel.h"


AssimpModel::AssimpModel(std::string const &t_path, bool t_gamma):
        Asset(),
        m_gamma_correction{t_gamma}
    {
        setAssetType(AssetType::Custom);
        loadModel(t_path);
    }

AssimpModel::~AssimpModel() {}

void AssimpModel::loadModel(const std::string &t_path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    m_directory = t_path.substr(0, t_path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void AssimpModel::processNode(aiNode *t_node, const aiScene *t_scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < t_node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = t_scene->mMeshes[t_node->mMeshes[i]];
        addMesh(processMesh(mesh, t_scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < t_node->mNumChildren; i++)
    {
        processNode(t_node->mChildren[i], t_scene);
    }
}

std::shared_ptr<Mesh> AssimpModel::processMesh(aiMesh *t_mesh, const aiScene *t_scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < t_mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = t_mesh->mVertices[i].x;
        vector.y = t_mesh->mVertices[i].y;
        vector.z = t_mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if(t_mesh->HasNormals()) {
            vector.x = t_mesh->mNormals[i].x;
            vector.y = t_mesh->mNormals[i].y;
            vector.z = t_mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(t_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = t_mesh->mTextureCoords[0][i].x;
            vec.y = t_mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        if(t_mesh->HasTangentsAndBitangents()) {
            vector.x = t_mesh->mTangents[i].x;
            vector.y = t_mesh->mTangents[i].y;
            vector.z = t_mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bitangent
            vector.x = t_mesh->mBitangents[i].x;
            vector.y = t_mesh->mBitangents[i].y;
            vector.z = t_mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < t_mesh->mNumFaces; i++)
    {
        aiFace face = t_mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = t_scene->mMaterials[t_mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<std::shared_ptr<Texture>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<std::shared_ptr<Texture>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    auto mesh_material = std::make_shared<Material>();
    if(!diffuseMaps.empty()){mesh_material->addDiffuseMap(diffuseMaps[0]);}
    if(!specularMaps.empty())mesh_material->addSpecularMap(specularMaps[0]);
    //mesh_material->addSpecularMap(textures[1]);

    // return a mesh object created from the extracted mesh data
    return std::make_shared<Mesh>(vertices, indices, mesh_material);
}

std::vector<std::shared_ptr<Texture>> AssimpModel::loadMaterialTextures(aiMaterial *t_mat, aiTextureType t_type, std::string t_type_name)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for(unsigned int i = 0; i < t_mat->GetTextureCount(t_type); i++)
    {
        aiString str;
        t_mat->GetTexture(t_type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < m_textures_loaded.size(); j++)
        {

            if(std::strcmp(m_textures_loaded[j]->getLocation().data(), str.C_Str()) == 0)
            {
                textures.emplace_back(m_textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            std::shared_ptr<Texture> texture = nullptr;
            if (t_type_name == "texture_diffuse") texture = std::make_shared<Texture>(m_directory + '/' + str.C_Str(),Texture::TextureType::DIFFUSE);
            else if (t_type_name == "texture_specular")texture = std::make_shared<Texture>(m_directory + '/' + str.C_Str(),Texture::TextureType::SPECULAR);
            //else if (t_type_name == "texture_normal") texture = std::make_shared<Texture>(m_directory + '/' + str.C_Str(),Texture::TextureType::DIFFUSE);
            //else if (t_type_name == "texture_height") texture = std::make_shared<Texture>(m_directory + '/' + str.C_Str(),Texture::TextureType::DIFFUSE);
            if(texture != nullptr){
                textures.emplace_back(texture);
                m_textures_loaded.emplace_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }

        }
    }
    return textures;
}



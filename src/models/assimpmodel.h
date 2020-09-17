//
// Created by Robin on 11/03/2020.
//

#ifndef ENGINE_ASSIMPMODEL_H
#define ENGINE_ASSIMPMODEL_H

#include <src/core/model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class AssimpModel : public Model {
    /**
     * Model loaded from a file
     */
public:
    /**
     * Constructor
     * @param path to the file
     * @param gamma
     */
    explicit AssimpModel(std::string const &path, bool gamma = false);

    /**
     * Destructor
     */
    ~AssimpModel();

private:

    void loadModel(const std::string &path);

    void processNode(aiNode *node, const aiScene *scene);

    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    std::shared_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);


private:
    std::vector<std::shared_ptr<Texture>> textures_loaded;
    std::string directory;
    bool gammaCorrection;

};


#endif //ENGINE_ASSIMPMODEL_H

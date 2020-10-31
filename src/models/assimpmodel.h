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
     * @param t_path to the file
     * @param t_gamma
     */
    explicit AssimpModel(std::string const &t_path, bool t_gamma = false);

    /**
     * Destructor
     */
    ~AssimpModel();

private:

    void loadModel(const std::string &t_path);

    void processNode(aiNode *t_node, const aiScene *t_scene);

    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *t_mat, aiTextureType t_type, std::string t_type_name);

    std::shared_ptr<Mesh> processMesh(aiMesh *t_mesh, const aiScene *t_scene);


private:
    std::vector<std::shared_ptr<Texture>> m_textures_loaded;
    std::string m_directory;
    bool m_gamma_correction;

};


#endif //ENGINE_ASSIMPMODEL_H

//
// Created by Robin on 22/02/2020.
//

#include "asset.h"

Asset::Asset():
        m_scale(1),
        m_translation(0),
        m_rotation(0),
        m_waiting_to_update{false}
    {}

Asset::~Asset()
{

}

void Asset::drawModel(Shader &tr_shader, GLuint t_glMode)
{

    if(m_waiting_to_update){
        m_waiting_to_update=false;
        updateModel();
    }
    tr_shader.setMat4("model", getModel());
    for(auto &m : m_meshs){
        m->drawMesh(tr_shader, t_glMode);
    }
}

void Asset::drawSelectionEdges(Shader &tr_shader, GLuint t_glMode) {
    if (isSelected()) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(-1, -1);
        tr_shader.setMat4("model", getModel());
        for(auto &m : m_meshs){
            m->drawMesh(tr_shader, t_glMode);
        }
        glDisable(GL_POLYGON_OFFSET_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Asset::addMesh(std::shared_ptr<Mesh> t_mesh)
{
    m_meshs.emplace_back(t_mesh);
}



void Asset::updateModel() {}

















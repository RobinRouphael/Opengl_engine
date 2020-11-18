//
// Created by robin on 15/11/2020.
//

#ifndef ENGINE_METABALL_H
#define ENGINE_METABALL_H


#include <src/core/asset.h>
#include <functional>
#include "marchingCube.h"

class MetaBall : public Asset {
public:
    struct Ball {
        glm::vec3 pos;
        float rad;
        float eval(glm::vec3 p);
    };
    MetaBall();
    ~MetaBall() override=default;

    void addBall();
    void removeBall();
    void updateModel() override;
    const std::vector<Ball> &getBalls(){return m_balls;}

    void setSelectedBall(int t_index){
        m_selected_ball=t_index;
    }

    void setBallPosition(const glm::vec3 &pos){
        m_balls[m_selected_ball].pos =pos;
        setWaitingToUpdate(true);
    }
    void setBallRadius(float radius){
        m_balls[m_selected_ball].rad=radius;
        setWaitingToUpdate(true);
    }
    void setCubeSize(float t_size){
        m_marching_cube.setCubeSize(t_size);
        setWaitingToUpdate(true);
    }
    void setIsoLevel(float t_level){
        m_marching_cube.setIsoLevel(t_level);
        setWaitingToUpdate(true);
    }
    float getIsolevel(){
        return m_marching_cube.getIsoLevel();
    }
    float getCubeSize(){
        return m_marching_cube.getCubeSize();
    }
private:

    std::vector<Ball> m_balls;
    MarchingCube m_marching_cube;
    int m_selected_ball{-1};

    std::function<float(glm::vec3)> m_iso_surface;
};


#endif //ENGINE_METABALL_H

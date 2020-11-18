//
// Created by robin on 15/11/2020.
//

#include "metaball.h"

MetaBall::MetaBall():
Asset(),
m_marching_cube{}
{
    m_iso_surface = [&](glm::vec3 p) {
        float val = 0.f;
        for (auto &ball : m_balls) val += ball.eval(p);
        return val;
    };
    m_balls.emplace_back(Ball{glm::vec3(0),1.f});
    setMeshs(std::vector<std::shared_ptr<Mesh>>{m_marching_cube.generateMesh(m_iso_surface)});
}

void MetaBall::addBall() {
    m_balls.emplace_back(Ball{glm::vec3(0),1.f});
    setWaitingToUpdate(true);
}

void MetaBall::updateModel() {
    setMeshs(std::vector<std::shared_ptr<Mesh>>{m_marching_cube.generateMesh(m_iso_surface)});
}

void MetaBall::removeBall() {
    m_balls.erase(m_balls.begin()+m_selected_ball);
    m_selected_ball=-1;
    setWaitingToUpdate(true);
}

float MetaBall::Ball::eval(glm::vec3 p) {
    glm::vec3 dist = p - pos;
    return (rad * rad) / (dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
}

//
// Created by robin on 23/10/2020.
//

#ifndef ENGINE_QUAD_H
#define ENGINE_QUAD_H


#include <src/core/asset.h>

class ScreenQuad : public Asset {
public:
    ScreenQuad(float t_x, float t_y, float t_width, float t_height);
    ~ScreenQuad() override = default;

private:
    void setup();
private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;


};


#endif //ENGINE_QUAD_H

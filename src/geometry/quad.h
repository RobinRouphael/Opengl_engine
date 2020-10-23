//
// Created by robin on 23/10/2020.
//

#ifndef ENGINE_QUAD_H
#define ENGINE_QUAD_H


#include <src/core/model.h>

class ScreenQuad : public Model {
public:
    ScreenQuad(float x, float y, float width, float height);
    ~ScreenQuad() override = default;

    void addTexture(std::shared_ptr<Texture> t);

private:
    void setup();
private:
    float x_;
    float y_;
    float width_;
    float height_;


};


#endif //ENGINE_QUAD_H

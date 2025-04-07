#pragma once
#include "../libgl/Texture.h"
#include "../libgl/Vector3.h"

class Fence
{
public:
    Fence(float length, float height);
    void SetTexture(GLuint brickTexture);
    void Draw() const;

private:
    float m_length, m_height;
    GLuint m_texture;
};
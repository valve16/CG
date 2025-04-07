#pragma once
#include "../libgl/Texture.h"
#include "../libgl/Vector3.h"

class Porch
{
public:
    Porch(float width, float depth, float height);
    void SetTexture(GLuint brickTexture, GLuint roofTexture);
    void Draw() const;

private:
    float m_width, m_depth, m_height;
    GLuint m_brickTexture, m_roofTexture;
};
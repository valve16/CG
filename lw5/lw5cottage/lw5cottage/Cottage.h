#pragma once
#include "../libgl/Texture.h"

class Cottage
{
public:
    Cottage(float width, float depth, float height);
    void SetTextures(GLuint brickTexture, GLuint roofTexture, GLuint windowTexture, GLuint doorTexture, GLuint side);
    void Draw() const;

private:
    // x 
    float m_width;
    // y
    float m_depth;
    // z
    float m_height;

    GLuint m_brickTexture, m_roofTexture, m_windowTexture, m_doorTexture, m_sideTexture;
};
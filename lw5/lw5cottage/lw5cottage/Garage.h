#pragma once
#include "../libgl/Texture.h"
#include "../libgl/Vector3.h"

class Garage
{
public:
    Garage(float width, float depth, float height);
    void SetTextures(GLuint brickTexture, GLuint roofTexture, GLuint windowTexture, GLuint doorTexture);
    void Draw() const;

private:
    float m_width, m_depth, m_height;
    GLuint m_brickTexture, m_roofTexture, m_windowTexture, m_doorTexture, m_garageDoorTexture;
};
#pragma once
#include "../libgl/Texture.h"
#include "../libgl/Vector3.h"

class Ground
{
public:
    Ground(float size);
    void SetTexture(GLuint grassTexture);
    void Draw() const;

private:
    float m_size;
    GLuint m_grassTexture;
};
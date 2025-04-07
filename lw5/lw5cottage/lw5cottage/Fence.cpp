#include "Fence.h"

Fence::Fence(float length, float height)
    : m_length(length), m_height(height) {
}

void Fence::SetTexture(GLuint texture)
{
    m_texture = texture;
}

void Fence::Draw() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // лицевая сторона
    glBegin(GL_QUADS);
    {
        CVector3f p0(-m_length / 2, 0, 0);
        CVector3f p1(m_length / 2, 0, 0);
        CVector3f p2(m_length / 2, 0, m_height);
        CVector3f p3(-m_length / 2, 0, m_height);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();
        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(3, 0); glVertex3fv(p1);
        glTexCoord2f(3, 1); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();
     //обратная сторона
    glBegin(GL_QUADS);
    {
        CVector3f p0(-m_length / 2, 0, 0);
        CVector3f p1(-m_length / 2, 0, m_height);
        CVector3f p2(m_length / 2, 0, m_height);
        CVector3f p3(m_length / 2, 0, 0);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();
        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0, 1); glVertex3fv(p1);
        glTexCoord2f(3, 1); glVertex3fv(p2);
        glTexCoord2f(3, 0); glVertex3fv(p3);
    }
    glEnd();
}
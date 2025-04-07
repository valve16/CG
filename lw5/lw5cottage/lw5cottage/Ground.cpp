#include "Ground.h"

Ground::Ground(float size)
    : m_size(size) {
}

void Ground::SetTexture(GLuint grassTexture)
{
    m_grassTexture = grassTexture;
}

void Ground::Draw() const
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_grassTexture);
    glBegin(GL_QUADS);

    CVector3f p0(-m_size / 2, -m_size / 2, 0);
    CVector3f p1(-m_size / 2, m_size / 2, 0);
    CVector3f p2(m_size / 2, m_size / 2, 0);
    CVector3f p3(m_size / 2, -m_size / 2, 0);

    CVector3f v1 = p1 - p0;
    CVector3f v2 = p2 - p0;
    CVector3f normal = Cross(v2, v1);
    normal.Normalize();
    glNormal3fv(normal);

    glTexCoord2f(0, 0); glVertex3fv(p0);
    glTexCoord2f(0, 10); glVertex3fv(p1);
    glTexCoord2f(10, 10); glVertex3fv(p2);
    glTexCoord2f(10, 0); glVertex3fv(p3);
    glEnd();
}
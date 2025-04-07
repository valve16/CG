#include "Porch.h"

Porch::Porch(float width, float depth, float height)
    : m_width(width), m_depth(depth), m_height(height) {
}

void Porch::SetTexture(GLuint brickTexture, GLuint roofTexture)
{
    m_brickTexture = brickTexture;
    m_roofTexture = roofTexture;
}

void Porch::Draw() const
{
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_brickTexture);
    glBegin(GL_QUADS);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, m_height);
        CVector3f p1(-m_width / 2, m_depth / 2, m_height);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(m_width / 2, -m_depth / 2, m_height);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0, 1); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(1, 0); glVertex3fv(p3);
    }
    glEnd();

    glBegin(GL_QUADS);
    {

        CVector3f p0(-m_width / 2, m_depth / 2, 0);
        CVector3f p1(m_width / 2, m_depth / 2, 0);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, m_depth / 2, m_height);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 0.1); glVertex3fv(p2);
        glTexCoord2f(0, 0.1); glVertex3fv(p3);
    }
    glEnd();


    glBegin(GL_QUADS);
    {

        CVector3f p0(m_width / 2, m_depth / 2, 0);
        CVector3f p1(m_width / 2, -m_depth / 2, 0);
        CVector3f p2(m_width / 2, -m_depth / 2, m_height);
        CVector3f p3(m_width / 2, m_depth / 2, m_height);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 0.1); glVertex3fv(p2);
        glTexCoord2f(0, 0.1); glVertex3fv(p3);
    }
    glEnd();

    glBegin(GL_QUADS);
    {

        CVector3f p0(-m_width / 2, -m_depth / 2, 0);
        CVector3f p1(-m_width / 2, m_depth / 2, 0);
        CVector3f p2(-m_width / 2, m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, -m_depth / 2, m_height);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 0.1); glVertex3fv(p2);
        glTexCoord2f(0, 0.1); glVertex3fv(p3);
    }
    glEnd();


    glBindTexture(GL_TEXTURE_2D, m_roofTexture);
    glBegin(GL_QUADS);
    {

        CVector3f p0( -1, -1, 3.5);
        CVector3f p1( -1, 1, 2.5);
        CVector3f p2(2, 1, 2.5);
        CVector3f p3(2, -1, 3.5);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);

        glTexCoord2f(1, 1); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(0, 0); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();
}
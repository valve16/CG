#include "Garage.h"

Garage::Garage(float width, float depth, float height)
    : m_width(width), m_depth(depth), m_height(height) {
}

void Garage::SetTextures(GLuint brickTexture, GLuint roofTexture, GLuint windowTexture, GLuint doorTexture)
{
    m_brickTexture = brickTexture;
    m_roofTexture = roofTexture;
    m_windowTexture = windowTexture;
    m_garageDoorTexture = doorTexture;
}

void Garage::Draw() const
{
    glEnable(GL_TEXTURE_2D);

    // Стены
    glBindTexture(GL_TEXTURE_2D, m_brickTexture);
 //передняя стена
    glBegin(GL_POLYGON);
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
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();

    //задняя стена
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, 0);
        CVector3f p1(-m_width / 2, -m_depth / 2, m_height);
        CVector3f p2(m_width / 2, -m_depth / 2, m_height);
        CVector3f p3(m_width / 2, -m_depth / 2, 0);

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

    //справа от входа
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, 0);
        CVector3f p1(-m_width / 2, m_depth / 2, 0);
        CVector3f p2(-m_width / 2, m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, -m_depth / 2, 3.5);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);

        //  p0, p2, p3
        float texV3 = 3.5f / m_height; // Пропорция для p3
        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(0, texV3); glVertex3fv(p3);
    }
    glEnd();



    //слева от входа
    glBegin(GL_POLYGON);
    {
        CVector3f p0(m_width / 2, -m_depth / 2, 0);
        CVector3f p1(m_width / 2, -m_depth / 2, 3.5);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(m_width / 2, m_depth / 2, 0);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();

        float texV3 = 3.5f / m_height;

        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0, texV3); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);

        glNormal3fv(normal);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(1, 0); glVertex3fv(p3);
    }
    glEnd();

    // Крыша
    glBindTexture(GL_TEXTURE_2D, m_roofTexture);
    glBegin(GL_QUADS);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, 3.5);
        CVector3f p1(-m_width / 2, m_depth / 2, m_height);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(m_width / 2, -m_depth / 2, 3.5);

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

    // Окно
    glBindTexture(GL_TEXTURE_2D, m_windowTexture);
    glBegin(GL_QUADS);
    {
        CVector3f p0(-0.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
        CVector3f p1(0.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
        CVector3f p2(0.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);
        CVector3f p3(-0.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();
        glNormal3fv(normal);

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();

    // ворота
    glBindTexture(GL_TEXTURE_2D, m_garageDoorTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2 - 0.01, -1.2, 0);
        CVector3f p1(-m_width / 2 - 0.01, 1.2, 0);
        CVector3f p2(-m_width / 2 - 0.01, 1.2, 2);
        CVector3f p3(-m_width / 2 - 0.01, -1.2, 2);

        CVector3f v1 = p1 - p0;
        CVector3f v2 = p2 - p0;
        CVector3f normal = Cross(v2, v1);
        normal.Normalize();
        glNormal3fv(normal);

        glTexCoord2f(1, 1); glVertex3fv(p0); 
        glTexCoord2f(0, 1); glVertex3fv(p1); 
        glTexCoord2f(0, 0); glVertex3fv(p2); 
        glTexCoord2f(1, 0); glVertex3fv(p3);
    }
    glEnd();
}
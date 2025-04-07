#include "Cottage.h"
#include "../libgl/Vector3.h"

Cottage::Cottage(float width, float depth, float height)
    : m_width(width), m_depth(depth), m_height(height) {
}

void Cottage::SetTextures(GLuint brickTexture, GLuint roofTexture, GLuint windowTexture, GLuint doorTexture, GLuint side)
{
    m_brickTexture = brickTexture;
    m_roofTexture = roofTexture;
    m_windowTexture = windowTexture;
    m_doorTexture = doorTexture;
    m_sideTexture = side;
}

void Cottage::Draw() const
{
    glEnable(GL_TEXTURE_2D);

    // �����
    glBindTexture(GL_TEXTURE_2D, m_brickTexture);

    //�������� �����
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, m_depth / 2, 0);
        CVector3f p1(m_width / 2, m_depth / 2, 0);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, m_depth / 2, m_height);

        CVector3f normal1(0, 1, 0);
        glNormal3fv(normal1); 

        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();

    //������ �����
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, 0);
        CVector3f p1(-m_width / 2, -m_depth / 2, m_height);
        CVector3f p2(m_width / 2, -m_depth / 2, m_height);
        CVector3f p3(m_width / 2, -m_depth / 2, 0);

        CVector3f normal1(0, -1, 0);

        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0, 1); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(1, 0); glVertex3fv(p3);
    }
    glEnd();

    //������ �� �����
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, -m_depth / 2, 0);
        CVector3f p1(-m_width / 2, m_depth / 2, 0);
        CVector3f p2(-m_width / 2, m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, -m_depth / 2, m_height);

        CVector3f normal1(1, 0, 0);

        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(1, 0); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(0, 1); glVertex3fv(p3);
    }
    glEnd();


    //����� �� �����
    glBegin(GL_POLYGON);
    {
        CVector3f p0(m_width / 2, -m_depth / 2, 0);
        CVector3f p1(m_width / 2, -m_depth / 2, m_height);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(m_width / 2, m_depth / 2, 0);

        CVector3f normal1(-1, 0, 0);
        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0, 1); glVertex3fv(p1);
        glTexCoord2f(1, 1); glVertex3fv(p2);
        glTexCoord2f(1, 0); glVertex3fv(p3);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_sideTexture);
    // ����� ������
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2 , -m_depth / 2, m_height);
        CVector3f p1(-m_width / 2 , m_depth / 2, m_height);
        CVector3f p2(-m_width / 2 , 0, m_height * 1.5);

        CVector3f normal1(1, 0, 0);

        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0.8, 0); glVertex3fv(p1);
        glTexCoord2f(0.5, 0.8); glVertex3fv(p2);
    }
    glEnd();


    // ����� �����
    glBegin(GL_POLYGON);
    {
        CVector3f p0(m_width / 2, m_depth / 2, m_height);
        CVector3f p1(m_width / 2, -m_depth / 2, m_height);
        CVector3f p2(m_width / 2, 0, m_height * 1.5);

        CVector3f normal1(1, 0, 0);

        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3fv(p0);
        glTexCoord2f(0.8, 0); glVertex3fv(p1);
        glTexCoord2f(0.5, 0.8); glVertex3fv(p2);
    }
    glEnd();

    // ����� (�������� ����)
    glBindTexture(GL_TEXTURE_2D, m_roofTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, 0, m_height * 1.5);
        CVector3f p1(-m_width / 2, m_depth / 2, m_height);
        CVector3f p2(m_width / 2, m_depth / 2, m_height);
        CVector3f p3(m_width / 2, 0, m_height * 1.5);
        // ��������� �������
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

    // ����� (������ ����)
    glBindTexture(GL_TEXTURE_2D, m_roofTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f p0(-m_width / 2, 0, m_height * 1.5);
        CVector3f p1(m_width / 2, 0, m_height * 1.5);
        CVector3f p2(m_width / 2, -m_depth / 2, m_height);
        CVector3f p3(-m_width / 2, -m_depth / 2, m_height);

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

    // ���� ������
    glBindTexture(GL_TEXTURE_2D, m_windowTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f normal1(0, 1, 0);
        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3f(-m_width / 2 + 0.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
        glTexCoord2f(1, 0); glVertex3f(-m_width / 2 + 1.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
        glTexCoord2f(1, 1); glVertex3f(-m_width / 2 + 1.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);
        glTexCoord2f(0, 1); glVertex3f(-m_width / 2 + 0.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);
    }
    glEnd();

    // ���� �����
    glBindTexture(GL_TEXTURE_2D, m_windowTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f normal1(0, 1, 0);
        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3f(m_width / 2 - 0.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
        glTexCoord2f(0, 1); glVertex3f(m_width / 2 - 0.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);
        glTexCoord2f(1, 1); glVertex3f(m_width / 2 - 1.5, m_depth / 2 + 0.01, m_height / 2 + 0.5);
        glTexCoord2f(1, 0); glVertex3f(m_width / 2 - 1.5, m_depth / 2 + 0.01, m_height / 2 - 0.5);
    }
    glEnd();

    // ���� �����
    glBindTexture(GL_TEXTURE_2D, m_windowTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f normal1(0, -1, 0);
        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3f(-1, -m_depth / 2 - 0.01, m_height / 2 - 0.5);
        glTexCoord2f(0, 1); glVertex3f(-1, -m_depth / 2 - 0.01, m_height / 2 + 0.5);
        glTexCoord2f(2, 1); glVertex3f(1, -m_depth / 2 - 0.01, m_height / 2 + 0.5);
        glTexCoord2f(2, 0); glVertex3f(1, -m_depth / 2 - 0.01, m_height / 2 - 0.5);
    }
    glEnd();


    // �����
    glBindTexture(GL_TEXTURE_2D, m_doorTexture);
    glBegin(GL_POLYGON);
    {
        CVector3f normal1(0, 1, 0);
        glNormal3fv(normal1);
        glTexCoord2f(0, 0); glVertex3f(-0.5, m_depth / 2 + 0.01, 0.5);
        glTexCoord2f(1, 0); glVertex3f(0.5, m_depth / 2 + 0.01, 0.5);
        glTexCoord2f(1, 1); glVertex3f(0.5, m_depth / 2 + 0.01, 2.5);
        glTexCoord2f(0, 1); glVertex3f(-0.5, m_depth / 2 + 0.01, 2.5);
    }
    glEnd();
}
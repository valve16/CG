#include "stdafx.h"
#include "Cube.h"

Cube::Cube(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	SetSideColor(CubeSide::NEGATIVE_X, defaultColor);
	SetSideColor(CubeSide::POSITIVE_X, defaultColor);
	SetSideColor(CubeSide::NEGATIVE_Y, defaultColor);
	SetSideColor(CubeSide::POSITIVE_Y, defaultColor);
	SetSideColor(CubeSide::NEGATIVE_Z, defaultColor);
	SetSideColor(CubeSide::POSITIVE_Z, defaultColor);
}

void Cube::Draw() const
{

	/*
	   Y
	   |
	   |
	   |
	   +---X
	  /
	 /
	Z
	   3----2
	  /    /|
	 /    / |
	7----6  |
	|  0 |  1
	|    | /
	|    |/
	4----5
	*/
	// ������ ��������� ������
	static constexpr float vertices[8][3] = {
		{ -1, -1, -1 }, // 0
		{ +1, -1, -1 }, // 1
		{ +1, +1, -1 }, // 2
		{ -1, +1, -1 }, // 3
		{ -1, -1, +1 }, // 4
		{ +1, -1, +1 }, // 5
		{ +1, +1, +1 }, // 6
		{ -1, +1, +1 }, // 7
	};

	// ������ ��������� ������ (� �������, ����������� �
	// �������� ���������� �� � ������� ������)
	// ������� ������ ������ ������������� � ������� �� ������
	// ������ ������� ������� (���� �������� �� ����� �������)
	static constexpr unsigned char faces[6][4] = {
		{ 4, 7, 3, 0 }, // ����� x<0
		{ 5, 1, 2, 6 }, // ����� x>0
		{ 4, 0, 1, 5 }, // ����� y<0
		{ 7, 6, 2, 3 }, // ����� y>0
		{ 0, 3, 2, 1 }, // ����� z<0
		{ 4, 5, 6, 7 }, // ����� z>0
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	glEnable(GL_COLOR_MATERIAL);
	// ���� ������� ����� ��������� ��������� � ������� ������ ���������
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specularColor));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	glBegin(GL_QUADS);
	{
		for (size_t face = 0; face < faceCount; ++face)
		{
			// ������������� ��������� � ������� ���� �����
			glColor4fv(glm::value_ptr(m_sideColors[face]));
			const unsigned char* facePoints = faces[face];

			// �������� ������� ��������� ����� ����
			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);
			auto p3 = glm::make_vec3(vertices[facePoints[3]]);
			// ��������� ���������� ������ ���� � ������ ��� �������
			p0 *= m_size * 0.5f;
			p1 *= m_size * 0.5f;
			p2 *= m_size * 0.5f;
			p3 *= m_size * 0.5f;

			// ��������� ������� � ����� ���� �����
			// ��������� ������������ ��� ������� ������
			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));

			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
			glVertex3fv(glm::value_ptr(p3));
		}
	}
	glEnd();
}

void Cube::SetSideColor(CubeSide side, const glm::vec4& color)
{
	unsigned index = static_cast<unsigned>(side);
	m_sideColors[index] = color;
}

void Cube::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Cube::SetShininess(float shininess)
{
	m_shininess = shininess;
}
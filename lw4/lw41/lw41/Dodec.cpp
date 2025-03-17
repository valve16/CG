#include "stdafx.h"
#include "Dodec.h"
#include "iostream"

// Золотое сечение для вычисления координат вершин додекаэдра
const float PHI = (1.0f + std::sqrt(5.0f)) / 2.0f;

Dodecahedron::Dodecahedron(float size)
	: m_size(size)
{
	constexpr glm::vec4 defaultColor{ 1, 1, 1, 1 };
	for (int i = 0; i < 12; ++i) {
		SetFaceColor(static_cast<DodecahedronFace>(i), defaultColor);
	}
}

void Dodecahedron::Draw() const
{
	// Координаты вершин додекаэдра (нормализованные)
	const std::vector<glm::vec3> vertices = {
			{ -1, -1, -1 },         // 0
			{ 0, -PHI, -1 / PHI },  // 1
			{ 1, -1, -1 },          // 2
			{ 1 / PHI, 0, -PHI },   // 3
			{ -1 / PHI, 0, -PHI },  // 4
			{ -PHI, -1 / PHI, 0 },  // 5
			{ -1, -1, 1 },          // 6
			{ 0, -PHI, 1 / PHI },   // 7
			{ 1, -1, 1 },           // 8
			{ PHI, -1 / PHI, 0 },   // 9
			{ PHI, 1 / PHI, 0 },    // 10
			{ 1, 1, -1 },           // 11
			{ 0, PHI, -1 / PHI },   // 12
			{ -1, 1, -1 },          // 13
			{ -PHI, 1 / PHI, 0 },   // 14
			{ -1 / PHI, 0, PHI },   // 15
			{ 1 / PHI, 0, PHI },    // 16
			{ 1, 1, 1 },            // 17
			{ 0, PHI, 1 / PHI },    // 18
			{ -1, 1, 1 }            // 19
	};

	// Определение граней додекаэдра 
	const std::vector<std::vector<int>> faces = {
		{ 0, 4, 3, 2, 1 },    // FACE_0
		{ 0, 1, 7, 6, 5 },    // FACE_1
		{ 1, 2, 9, 8, 7 },     // FACE_2
		{ 2, 3, 11, 10, 9 },    // FACE_3
		{ 4, 13, 12, 11, 3 },    // FACE_4
		{ 5, 14, 13, 4, 0 },     // FACE_5
		{ 5, 6, 15, 19, 14 },   // FACE_6
		{ 6, 7, 8, 16, 15 },   // FACE_7
		{ 8, 9, 10, 17, 16 },   // FACE_8
		{ 18, 17, 10, 11, 12 },   // FACE_9
		{ 14, 19, 18, 12, 13 },    // FACE_10
		{ 15, 16, 17, 18, 19 }    // FACE_11
	};
	const size_t faceCount = faces.size();

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

	//glDisable(GL_CULL_FACE);
	glLineWidth(3.0f);

	for (size_t face = 0; face < faces.size(); ++face)
	{
		glBegin(GL_POLYGON);
		{
			glColor4fv(glm::value_ptr(m_faceColors[face]));
			const std::vector<int>& facePoints = faces[face];

			// Получаем вершины текущей грани
			auto p0 = glm::make_vec3(vertices[facePoints[0]]);
			auto p1 = glm::make_vec3(vertices[facePoints[1]]);
			auto p2 = glm::make_vec3(vertices[facePoints[2]]);
			auto p3 = glm::make_vec3(vertices[facePoints[3]]);
			auto p4 = glm::make_vec3(vertices[facePoints[4]]);

			// Масштабируем с учетом размера
			p0 *= m_size * 0.5f;
			p1 *= m_size * 0.5f;
			p2 *= m_size * 0.5f;
			p3 *= m_size * 0.5f;
			p4 *= m_size * 0.5f;

			// Вычисляем нормаль через векторное произведение
			auto v01 = p1 - p0;
			auto v02 = p2 - p0;
			auto normal = glm::normalize(glm::cross(v01, v02));

			glNormal3fv(glm::value_ptr(normal));
			glVertex3fv(glm::value_ptr(p0));
			glVertex3fv(glm::value_ptr(p1));
			glVertex3fv(glm::value_ptr(p2));
			glVertex3fv(glm::value_ptr(p3));
			glVertex3fv(glm::value_ptr(p4));
			glVertex3fv(glm::value_ptr(p0));
		}
		glEnd();
	}

	//glEnable(GL_CULL_FACE);
}

void Dodecahedron::SetFaceColor(DodecahedronFace face, const glm::vec4& color)
{
	unsigned index = static_cast<unsigned>(face);
	m_faceColors[index] = color;
}

void Dodecahedron::SetSpecularColor(glm::vec4 color)
{
	m_specularColor = color;
}

void Dodecahedron::SetShininess(float shininess)
{
	m_shininess = shininess;
}
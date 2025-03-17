#pragma once

enum class DodecahedronFace
{
    FACE_0, FACE_1, FACE_2, FACE_3, FACE_4,
    FACE_5, FACE_6, FACE_7, FACE_8, FACE_9,
    FACE_10, FACE_11
};

class Dodecahedron
{
public:
    explicit Dodecahedron(float size = 1);
    void Draw() const;

    void SetFaceColor(DodecahedronFace face, const glm::vec4& color);
    void SetSpecularColor(glm::vec4 color);
    void SetShininess(float shininess);

private:
    float m_size;
    glm::vec4 m_faceColors[12];
    glm::vec4 m_specularColor = { 0, 0, 0, 1 };
    float m_shininess = 1;

};
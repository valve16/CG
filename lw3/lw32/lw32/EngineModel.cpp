#include "StdAfx.h"
#include "EngineModel.h"

EngineModel::EngineModel() : m_pistonY(0.1f), m_cycleTime(0.0f) {}


void EngineModel::Update(float deltaTime) {
    const float rotationSpeed = 180.0f;
    m_crankshaftAngle += rotationSpeed * deltaTime;

    float normalizedAngle = fmod(m_crankshaftAngle, 720.0f);
    if (normalizedAngle < 0) normalizedAngle += 720.0f; 

    if (normalizedAngle >= 30 && normalizedAngle < 180) {
        m_tact = 1; 
    }
    else if (normalizedAngle >= 180 && normalizedAngle < 360) {
        m_exhaustParticles.clear();
        
        m_tact = 2; 
    }
    else if (normalizedAngle >= 360 && normalizedAngle < 540) {
        m_intakeParticles.clear();
        m_tact = 3; 
    }
    else if (normalizedAngle >= 540 && normalizedAngle < 690) {
        m_tact = 4; 
    }
    else
    {
        m_tact = 0;
    }

    if (normalizedAngle >= 360 && normalizedAngle <= 400)
    {
        m_ignition = true;
    }
    else
    {
        m_ignition = false;
    }

    float openY = -0.05f;  
    float closeY = 0.0f;   

    if (m_tact == 1 || m_tact == 4) {
        m_valvePositionY = openY;
    }
    else {
        m_valvePositionY = closeY;
    }


    CreateParticles();
    UpdateParticles(deltaTime);

}

void EngineModel::Draw()
{
    // картер
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.98f); 
    glVertex2f(0.4f, -0.98f);   
    glVertex2f(0.4f, -0.6f);   
    glVertex2f(0.25f, -0.55f);
    glVertex2f(-0.25f, -0.55f);
    glVertex2f(-0.4f, -0.6f);
    glEnd();

    // Внешний корпус цилиндра

    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, -0.55f); 
    glVertex2f(0.25f, -0.55f);  
    glVertex2f(0.25f, 0.25f);   
    glVertex2f(-0.25f, 0.25f);  
    glEnd();

    // ГРМ
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.25f);
    glVertex2f(0.4f, 0.25f);  
    glVertex2f(0.4f, 0.45f);   
    glVertex2f(-0.4f, 0.45f);  
    glEnd();

    //впуск(канал)

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(-0.15f, 0.3f);
    glVertex2f(-0.15f, 0.4f);
    glVertex2f(-0.4f, 0.4f);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22f, 0.3f);
    glVertex2f(-0.15f, 0.4f);
    glVertex2f(-0.055f, 0.2f);
    glVertex2f(-0.143f, 0.15f);
    glEnd();


    //выпуск(канал)

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.15f, 0.4f);
    glVertex2f(0.4f, 0.4f);
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(0.22f, 0.3f);
    glVertex2f(0.15f, 0.4f);
    glVertex2f(0.055f, 0.2f);
    glVertex2f(0.143f, 0.15f);
    glEnd();
   

    // Корпус цилиндра
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.5f); glVertex2f(0.2f, -0.5f);
    glVertex2f(0.2f, 0.2f); glVertex2f(0.0f, 0.3f); glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Контур
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(-0.2f, -0.5f); 
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.2f, -0.5f);
    glVertex2f(0.2f, 0.2f); 
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.0f, 0.3f);
    glEnd();

    DrawSparkPlug();
    DrawCrankshaft();
    DrawValves();
    DrawParticles();
    DrawPiston();

}

void EngineModel::DrawPiston() {
    //шатун 

    // Основной корпус поршня
    glColor3f(0.2f, 0.2f, 0.2f); // Цвет шатуна
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, m_connCrankY + 0.70f); 
    glVertex2f(0.05f, m_connCrankY + 0.70f);  
    glVertex2f(m_connCrankX + 0.05f, m_connCrankY + 0.1f);
    glVertex2f(m_connCrankX - 0.05f, m_connCrankY + 0.1f);
    glEnd();
    m_pistonY = m_connCrankY + 0.70f;
    glColor3f(0.3f, 0.3f, 0.3f); 
    glBegin(GL_QUADS);
    glVertex2f(-0.18f, m_pistonY - 0.1f); 
    glVertex2f(0.18f, m_pistonY - 0.1f); 
    glVertex2f(0.18f, m_pistonY + 0.1f);
    glVertex2f(-0.18f, m_pistonY + 0.1f); 
    glEnd();

    // Отверстие для крепления шатуна
    DrawCircle(0.0f, m_pistonY, 0.03f, 20, 0.1f, 0.1f, 0.1f);

    DrawConnectingRodRing();
}

void EngineModel::DrawValves() const {

    //Впуск
    glColor3f(0.6f, 0.6f, 0.6f); 
    glPushMatrix(); 
    glTranslatef(-0.3f, 0.525f, 0.0f); 
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f); 

    glTranslatef(0.3f, -0.525f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.37f, 0.40f);
    glVertex2f(-0.23f, 0.40f);
    glVertex2f(-0.23f, 0.60f);
    glVertex2f(-0.37f, 0.60f);
    glEnd();
    // Впускной клапан
    if (m_tact == 1)
    {
        glTranslatef(0.0f, m_valvePositionY, 0.0f);
    }
    // Стержень 
    glColor3f(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
    glVertex2f(-0.32f, 0.5f);  
    glVertex2f(-0.28f, 0.5f);  
    glVertex2f(-0.28f, 0.23f);
    glVertex2f(-0.32f, 0.23f);
    glEnd();
    // Тарелка 
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, 0.18f);
    glVertex2f(-0.25f, 0.18f);
    glVertex2f(-0.28f, 0.23f);
    glVertex2f(-0.32f, 0.23f);
    glEnd();
    glPopMatrix();

    // Выпускной клапан
    glColor3f(0.6f, 0.6f, 0.6f);
    glPushMatrix();
    glTranslatef(0.3f, 0.525f, 0.0f); 
    glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
    
    glTranslatef(-0.3f, -0.525f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(0.37f, 0.40f);
    glVertex2f(0.23f, 0.40f);
    glVertex2f(0.23f, 0.60f);
    glVertex2f(0.37f, 0.60f);
    glEnd();

    if (m_tact == 4)
    {
        glTranslatef(0.0f, m_valvePositionY, 0.0f);
    }
    glColor3f(0.7f, 0.7f, 0.7f);
    // Стержень 

    glBegin(GL_QUADS);
    glVertex2f(0.32f, 0.5f);
    glVertex2f(0.28f, 0.5f);
    glVertex2f(0.28f, 0.23f);
    glVertex2f(0.32f, 0.23f);
    glEnd();

    // Тарелка 
    glBegin(GL_QUADS);
    glVertex2f(0.35f, 0.18f);
    glVertex2f(0.25f, 0.18f);
    glVertex2f(0.28f, 0.23f);
    glVertex2f(0.32f, 0.23f);
    glEnd();
    glPopMatrix();
}


void EngineModel::DrawSparkPlug() const {

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, 0.3f);  
    glVertex2f(0.05f, 0.3f);   
    glVertex2f(0.05f, 0.4f);   
    glVertex2f(-0.05f, 0.4f);  
    glEnd();

    glColor3f(0.9f, 0.9f, 0.9f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, 0.4f);
    glVertex2f(0.05f, 0.4f);
    glVertex2f(0.05f, 0.6f);
    glVertex2f(-0.05f, 0.6f);
    glEnd();

    // Электрод 
    glColor3f(0.3f, 0.3f, 0.3f); 
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.3f);   
    glVertex2f(0.0f, 0.25f);   
    glEnd();

    // Искра 
    if (m_ignition) {
        glColor3f(1.0f, 0.5f, 0.0f); // Оранжевый для искры
        glPointSize(15.0f);
        glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.25f);    // Точка искры
        glEnd();
    }
}
void EngineModel::DrawCircle(float cx, float cy, float radius, int segments, float r, float g, float b) const {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

void EngineModel::DrawConnectingRodRing()
{

    const float outerRadius = 0.12f; 
    const float innerRadius = 0.07f; 
    const int numSegments = 40; 
    const float centerX = 0.0f; // Координаты центра
    const float centerY = -0.62f;

    glPushMatrix();
    glTranslatef(m_crankCenterX, m_crankCenterY, 0.0f); 
    glRotatef(m_crankshaftAngle, 0.0f, 0.0f, 1.0f); 
    glTranslatef(-m_crankCenterX, -m_crankCenterY, 0.0f); 

    GLfloat matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    GLfloat transformedX = matrix[0] * centerX + matrix[4] * centerY + matrix[12];
    GLfloat transformedY = matrix[1] * centerX + matrix[5] * centerY + matrix[13];


    glColor3f(0.1f, 0.1f, 0.1f); 
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.14159f * i / numSegments;
        float cosA = cos(angle);
        float sinA = sin(angle);


        glVertex2f(centerX + cosA * outerRadius, centerY + sinA * outerRadius);
        glVertex2f(centerX + cosA * innerRadius, centerY + sinA * innerRadius);
    }
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPopMatrix();

    //glPointSize(5.0f);
    //glBegin(GL_POINTS);
    //glVertex2f(transformedX, transformedY);
    m_connCrankX = transformedX;
    m_connCrankY = transformedY;
    glEnd();
    
}

void EngineModel::DrawCrankshaft() const 
{
    float centerX = m_crankCenterX;
    float centerY = m_crankCenterY;
    glPushMatrix(); 
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(m_crankshaftAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-centerX, -centerY, 0.0f);

    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.17f, -0.88f);
    glVertex2f(0.17f, -0.88f);
    glVertex2f(0.1f, -0.685f);
    glVertex2f(-0.1f, -0.685f);
    glEnd();

    glColor3f(0.6f, 0.6f, 0.6f);

    //glPointSize(5.0f);
    //glBegin(GL_POINTS);
    //glVertex2f(centerX, centerY);
    //glEnd();

    glPopMatrix();
}



void EngineModel::CreateParticles() {
    if (m_tact == 1) { 
        Point particle;
        particle.x = -0.17f;
        particle.y = 0.3f;
        particle.velocityX = 0.1f; 
        particle.velocityY = -0.1f; 
        m_intakeParticles.push_back(particle);
    }
    else if (m_tact == 4) { 
        Point particle;
        particle.x = 0.08f; 
        particle.y = 0.2f;
        particle.velocityX = 0.1f; 
        particle.velocityY = 0.1f; 
        m_exhaustParticles.push_back(particle);
    }
}

void EngineModel::DrawParticles() const {
    glColor3f(0.0f, 0.0f, 1.0f); 
    for (const auto& particle : m_intakeParticles) {
        glBegin(GL_POINTS);
        glVertex2f(particle.x, particle.y);
        glEnd();
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    for (const auto& particle : m_exhaustParticles) {
        glBegin(GL_POINTS);
        glVertex2f(particle.x, particle.y);
        glEnd();
    }
}

void EngineModel::UpdateParticles(float deltaTime) {
    // Обновление впускных частиц
    for (auto it = m_intakeParticles.begin(); it != m_intakeParticles.end();) {
        it->x += it->velocityX * deltaTime;
        it->y += it->velocityY * deltaTime;
        if (it->x > 1.0f) { 
            it = m_intakeParticles.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = m_exhaustParticles.begin(); it != m_exhaustParticles.end();) {
        it->x += it->velocityX * deltaTime;
        it->y += it->velocityY * deltaTime;
        if (it->x > 1.0f) { 
            it = m_exhaustParticles.erase(it);
        }
        else {
            ++it;
        }
    }
}
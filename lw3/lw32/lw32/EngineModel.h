#pragma once
#include <vector>
#include <utility>

class EngineModel {
public:
    struct Point 
    { 
        float x, y; 
        float velocityX, velocityY;
    };
    EngineModel();

    void Update(float deltaTime);

    void Draw();

private:
    float m_pistonY = 0.1f;         // Позиция поршня
    bool m_ignition = false;        // Вспышка топлива
    std::vector<Point> m_intakeParticles;
    std::vector<Point> m_exhaustParticles;
    float m_cycleTime = 0.0f;       // Время цикла
    float m_crankshaftAngle = 0.0f;

    int m_tact = 1;

    const float m_crankCenterX = 0.0f;
    const float m_crankCenterY = -0.75f;

    float m_connCrankX = 0.0f;
    float m_connCrankY = -0.62f;

    float m_valvePositionY = 0.0f;

    void DrawPiston() ;
    void DrawValves() const;

   
    void DrawSparkPlug() const;
    void DrawCircle(float cx, float cy, float radius, int segments, float r, float g, float b) const;
    void DrawConnectingRodRing();
    void DrawCrankshaft() const;
    void CreateParticles();
    void DrawParticles() const;
    void UpdateParticles(float deltaTime);
};
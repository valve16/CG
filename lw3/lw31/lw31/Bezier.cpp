#include "StdAfx.h"
#include "Bezier.h"

CBezier::CBezier()
{
    m_controlPoints.push_back({ -0.9f, -0.9f });
    m_controlPoints.push_back({ -0.35f, 0.0f });
    m_controlPoints.push_back({ 0.35f, 0.15f });
    m_controlPoints.push_back({ 0.9f, -0.9f });
}

const std::vector<CBezier::Point>& CBezier::GetControlPoints() const
{
    return m_controlPoints;
}

void CBezier::SetControlPoint(size_t index, const Point& point)
{
    if (index < m_controlPoints.size())
    {
        m_controlPoints[index] = point;
    }
}
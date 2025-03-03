// 
#include "StdAfx.h"
#include "BezierController.h"

BezierController::BezierController(std::shared_ptr<CBezier> model)
    : m_model(model), m_selectedPointIndex(-1), m_isDragging(false) {
}

void BezierController::OnLButtonDown(UINT nFlags, CPoint point, const CRect& clientRect) {
    if (!m_model) return;

    float width = static_cast<float>(clientRect.Width());
    float height = static_cast<float>(clientRect.Height());
    auto x = (point.x / width) * 2 - 1;
    auto y = 1 - (point.y / height) * 2;
    auto aspect = width / height;
    double viewHeight = 2;
    auto viewWidth = aspect * viewHeight;
    x = x * (viewWidth / 2);
    y = y * (viewHeight / 2);
   // std::cout << "Selected point: " << m_selectedPointIndex << std::endl;
    const auto& points = m_model->GetControlPoints();
    for (size_t i = 0; i < points.size(); ++i) {
        auto dx = x - points[i].first;
        auto dy = y - points[i].second;
        if (dx * dx + dy * dy < 0.01f) { 
            m_selectedPointIndex = i;
            m_isDragging = true;
            break;
        }
    }
}

void BezierController::OnMouseMove(UINT nFlags, CPoint point, const CRect& clientRect) {
    if (m_isDragging && m_model) {

        float width = static_cast<float>(clientRect.Width());
        float height = static_cast<float>(clientRect.Height());
        auto x = (point.x / width) * 2 - 1;
        auto y = 1 - (point.y / height) * 2;
        auto aspect = width / height;
        double viewHeight = 2;
        auto viewWidth = aspect * viewHeight;
        x = x * (viewWidth / 2);
        y = y * (viewHeight / 2);

        m_model->SetControlPoint(m_selectedPointIndex, { x, y });
    }
}

void BezierController::OnLButtonUp(UINT nFlags, CPoint point) {
    m_isDragging = false;
    m_selectedPointIndex = -1;
}
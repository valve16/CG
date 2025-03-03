//
#pragma once
#include "Bezier.h"
#include <atltypes.h>

class BezierController {
public:
    BezierController(std::shared_ptr<CBezier> model);
    void OnLButtonDown(UINT nFlags, CPoint point, const CRect& clientRect);
    void OnMouseMove(UINT nFlags, CPoint point, const CRect& clientRect);
    void OnLButtonUp(UINT nFlags, CPoint point);

private:
    std::shared_ptr<CBezier> m_model;
    size_t m_selectedPointIndex; 
    bool m_isDragging;         
};
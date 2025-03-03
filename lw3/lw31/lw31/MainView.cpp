#include "StdAfx.h"
#include "MainView.h"
#include "Bezier.h"

BOOL CMainView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

void CMainView::SetModel(std::shared_ptr<CBezier> model) {
    m_model = model;  
}

void CMainView::SetController(std::unique_ptr<BezierController> controller) {
    m_controller = std::move(controller); 
}
void CMainView::OnLButtonDown(UINT nFlags, CPoint point) {
    if (m_controller) {
        CRect rc;
        GetClientRect(rc);
        m_controller->OnLButtonDown(nFlags, point, rc);
    }
}

void CMainView::OnMouseMove(UINT nFlags, CPoint point) {
    if (m_controller) {
        CRect rc;
        GetClientRect(rc);
        m_controller->OnMouseMove(nFlags, point, rc);
        RedrawWindow();
    }
}

void CMainView::OnLButtonUp(UINT nFlags, CPoint point) {
    if (m_controller) {
        m_controller->OnLButtonUp(nFlags, point);
    }
}

void CMainView::DrawScene()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f);
    DrawAxes();

    if (m_model)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        DrawBezierCurve();

        glColor3f(0.0f, 1.0f, 0.0f);
        DrawControlPoints();
    }
}

void CMainView::DrawAxes()
{
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    for (float i = -1.0f; i <= 1.0f; i += 0.1f)
    {
        glBegin(GL_LINES);
        glVertex2f(i, -0.05f);
        glVertex2f(i, 0.05f);
        glVertex2f(-0.05f, i);
        glVertex2f(0.05f, i);
        glEnd();
    }
}

void CMainView::DrawBezierCurve()
{
    if (!m_model || m_model->GetControlPoints().size() != 4)
        return;

    const auto& points = m_model->GetControlPoints();
    const int BEZIER_POINTS = 100;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= BEZIER_POINTS; ++i)
    {
        float t = i / (float)BEZIER_POINTS;
        float x = pow(1 - t, 3) * points[0].first + 3 * t * pow(1 - t, 2) * points[1].first +
            3 * pow(t, 2) * (1 - t) * points[2].first + pow(t, 3) * points[3].first;
        float y = pow(1 - t, 3) * points[0].second + 3 * t * pow(1 - t, 2) * points[1].second +
            3 * pow(t, 2) * (1 - t) * points[2].second + pow(t, 3) * points[3].second;
        glVertex2f(x, y);
    }
    glEnd();
}

void CMainView::DrawControlPoints()
{
    if (!m_model)
        return;

    const auto& points = m_model->GetControlPoints();
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for (const auto& point : points)
    {
        glVertex2f(point.first, point.second);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    for (size_t i = 0; i < points.size() - 1; ++i)
    {
        glVertex2f(points[i].first, points[i].second);
        glVertex2f(points[i + 1].first, points[i + 1].second);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void CMainView::OnSize(UINT uMsg, CSize /*size*/)
{
    &uMsg;
    CRect rc;
    GetClientRect(rc);
    int width = rc.Width();
    int height = rc.Height();

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspect = (double)width / height;
    double viewHeight = 2;
    double viewWidth = aspect * viewHeight;

    glOrtho(
        -viewWidth / 2, +viewWidth / 2,
        -viewHeight / 2, +viewHeight / 2,
        -1, 1);

    glMatrixMode(GL_MODELVIEW);
}

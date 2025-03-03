#pragma once
#include "GLViewImp.h"
#include "Bezier.h"
#include "BezierController.h"

class CMainView : public CGLViewImpl<CMainView> {
public:
    DECLARE_WND_CLASS(NULL)

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    void SetModel(std::shared_ptr<CBezier> model);
    void SetController(std::unique_ptr<BezierController> controller);

    BEGIN_MSG_MAP(CMainView)
        MSG_WM_SIZE(OnSize)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        CHAIN_MSG_MAP(CGLViewImpl<CMainView>)
    END_MSG_MAP()

protected:
    virtual void DrawScene();
    void DrawAxes();
    void DrawBezierCurve();
    void DrawControlPoints();
    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnMouseMove(UINT nFlags, CPoint point);
    void OnLButtonUp(UINT nFlags, CPoint point);

private:
    void OnSize(UINT uMsg, CSize size);

    std::shared_ptr<CBezier> m_model;
    std::unique_ptr<BezierController> m_controller;
};
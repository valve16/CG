#pragma once
#include "GLViewImp.h"
#include "EngineModel.h"

class CMainView : public CGLViewImpl<CMainView> {
public:
    DECLARE_WND_CLASS(NULL)

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    void SetModel(std::shared_ptr<EngineModel> model);
    //void SetController(std::unique_ptr<BezierController> controller);

    BEGIN_MSG_MAP(CMainView)
        MSG_WM_SIZE(OnSize)
        CHAIN_MSG_MAP(CGLViewImpl<CMainView>)
    END_MSG_MAP()

protected:
    virtual void DrawScene();

private:
    void OnSize(UINT uMsg, CSize size);
    std::shared_ptr<EngineModel> m_model;
    DWORD m_lastTime = 0;
};
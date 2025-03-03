// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainFrm.h"
#include "OpenGL.h"
#include "aboutdlg.h"
#include "MainView.h"
#include "Bezier.h"


CMainFrame::CMainFrame() {
	m_model = std::make_shared<CBezier>();
	m_controller = std::make_unique<BezierController>(m_model); 
	m_view.SetModel(m_model);  
	m_view.SetController(std::move(m_controller));  
}
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
	{
		return TRUE;
	}

	return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	m_hWndClient = m_view.Create(*this, rcDefault, NULL, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);
	m_view.UpdateWindow();
	//m_view.SetModel(m_model);      
	//m_view.SetController(std::move(m_controller));

	return 0;
}

//LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
//{
//	// unregister message filtering and idle updates
//	CMessageLoop* pLoop = _Module.GetMessageLoop();
//	ATLASSERT(pLoop != NULL);
//	pLoop->RemoveMessageFilter(this);
//
//	pLoop->RemoveIdleHandler(this);
//
//	bHandled = FALSE;
//	return 1;
//}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}
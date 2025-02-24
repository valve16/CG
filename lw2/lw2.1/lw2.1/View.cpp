// sample05_simple_wtl_applicationView.cpp : implementation of the CSample05_simple_wtl_applicationView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "utils.h"

#include "View.h"


using namespace Gdiplus;
using namespace std;

BOOL CView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

CView::CView() : m_bDragging(false), m_offsetX(0), m_offsetY(0)
{
}


LRESULT CView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
	Graphics g(dc);

	RedrawBackBuffer();
	g.DrawImage(m_pBackBuffer.get(), 0, 0); 

	return 0;
}

bool CView::OpenPicture(std::wstring const& fileName)
{
	Image img(fileName.c_str());
	if (img.GetLastStatus() == Ok)
	{
		m_pPicture.reset(new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB));

		Graphics g(m_pPicture.get());

		std::wstring ext = fileName.substr(fileName.find_last_of(L".") + 1);
		std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);
		m_isPNG = (ext == L"png");

		g.DrawImage(&img, 0, 0);

		InvalidateRect(NULL);
		return true;
	}

	return false;

}


bool CView::SavePicture(std::wstring const& fileName, int quality)
{
	if (m_pPicture.get())
	{
		return CUtils::SaveImage(fileName, *m_pPicture, quality);
	}

	return false;
}

void CView::ClosePicture(void)
{
	m_pPicture.release();
	InvalidateRect(NULL);
}

LRESULT CView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pPicture.get())
	{
		m_bDragging = true;
		m_lastPoint.x = GET_X_LPARAM(lParam);
		m_lastPoint.y = GET_Y_LPARAM(lParam);
		SetCapture();
	}
	return 0;
}

LRESULT CView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bDragging)
	{
		m_bDragging = false;
		ReleaseCapture();
	}
	return 0;
}

LRESULT CView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bDragging && (wParam & MK_LBUTTON))
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		m_offsetX += (x - m_lastPoint.x);
		m_offsetY += (y - m_lastPoint.y);

		m_lastPoint.x = x;
		m_lastPoint.y = y;

		InvalidateRect(NULL);
	}
	return 0;
}

LRESULT CView::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/,
	LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// ничего не делаем
	return 0;
}


void CView::RedrawBackBuffer(void)
{

	CRect rc;
	GetClientRect(&rc);
	m_pBackBuffer.reset(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));


	Graphics g(m_pBackBuffer.get());

	g.Clear(Color(0xdd, 0xdd, 0xdd));

	if (m_isPNG)
	{
		DrawCheckerboardBackground(g, rc.Width(), rc.Height());
	}

	if (m_pPicture.get())
	{
		g.DrawImage(m_pPicture.get(), m_offsetX, m_offsetY); 
	}
}

void CView::DrawCheckerboardBackground(Gdiplus::Graphics& g, int width, int height)
{
	const int tileSize = 20;
	Gdiplus::Color color1(0xFF, 0xCC, 0xCC, 0xCC); 
	Gdiplus::Color color2(0xFF, 0xEE, 0xEE, 0xEE);

	for (int y = 0; y < height; y += tileSize)
	{
		for (int x = 0; x < width; x += tileSize)
		{
			Gdiplus::Color color = ((x / tileSize + y / tileSize) % 2 == 0) ? color1 : color2;
			Gdiplus::SolidBrush brush(color);

			g.FillRectangle(&brush, x, y, tileSize, tileSize);
		}
	}
}

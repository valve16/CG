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

CView::CView() : m_bDrawing(false),
				m_isPNG(false),
				m_drawColor(Color::Red),
				m_brushSize(5),
				m_scrollPosX(0),
				m_scrollPosY(0)
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

		UpdateScrollBars();
		InvalidateRect(NULL);
		return true;
	}

	return false;

}


LRESULT CView::OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nScrollCode = (int)LOWORD(wParam);
	int nPos = (short)HIWORD(wParam);

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_HORZ, &si);

	switch (nScrollCode)
	{
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
	case SB_LINELEFT:
		si.nPos -= 10;
		break;
	case SB_LINERIGHT:
		si.nPos += 10;
		break;
	case SB_PAGELEFT:
		si.nPos -= si.nPage;
		break;
	case SB_PAGERIGHT:
		si.nPos += si.nPage;
		break;
	}

	si.nPos = max(si.nMin, min(si.nPos, si.nMax - (int)si.nPage));
	SetScrollInfo(SB_HORZ, &si, TRUE);
	m_scrollPosX = si.nPos;

	InvalidateRect(NULL);
	return 0;
}

LRESULT CView::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nScrollCode = (int)LOWORD(wParam);
	int nPos = (short)HIWORD(wParam);

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(SB_VERT, &si);

	switch (nScrollCode)
	{
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
	case SB_LINEUP:
		si.nPos -= 10;
		break;
	case SB_LINEDOWN:
		si.nPos += 10;
		break;
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;
	}

	si.nPos = max(si.nMin, min(si.nPos, si.nMax - (int)si.nPage));
	SetScrollInfo(SB_VERT, &si, TRUE);
	m_scrollPosY = si.nPos;

	InvalidateRect(NULL);
	return 0;
}

void CView::UpdateScrollBars()
{
	if (!m_pPicture.get())
	{
		SetScrollRange(SB_HORZ, 0, 0, TRUE);
		SetScrollRange(SB_VERT, 0, 0, TRUE);
		return;
	}

	CRect rc;
	GetClientRect(&rc);

	int imageWidth = m_pPicture->GetWidth();
	int imageHeight = m_pPicture->GetHeight();

	SCROLLINFO si = { sizeof(SCROLLINFO), SIF_RANGE | SIF_PAGE | SIF_POS };

	si.nMin = 0;
	si.nMax = max(imageWidth - 1, rc.Width() - 1);
	si.nPage = rc.Width();
	si.nPos = min(m_scrollPosX, si.nMax - (int)si.nPage);
	SetScrollInfo(SB_HORZ, &si, TRUE);
	m_scrollPosX = si.nPos;

	si.nMax = max(imageHeight - 1, rc.Height() - 1);
	si.nPage = rc.Height();
	si.nPos = min(m_scrollPosY, si.nMax - (int)si.nPage);
	SetScrollInfo(SB_VERT, &si, TRUE);
	m_scrollPosY = si.nPos;
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
		m_bDrawing = true;
		m_lastPoint.x = GET_X_LPARAM(lParam) + m_scrollPosX;
		m_lastPoint.y = GET_Y_LPARAM(lParam) + m_scrollPosY;
		SetCapture();
	}
	return 0;
}

LRESULT CView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bDrawing)
	{
		m_bDrawing = false;
		ReleaseCapture();
	}
	return 0;
}

LRESULT CView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bDrawing && (wParam & MK_LBUTTON))
	{
		int x = GET_X_LPARAM(lParam) + m_scrollPosX;
		int y = GET_Y_LPARAM(lParam) + m_scrollPosY;

		DrawLine(m_lastPoint.x, m_lastPoint.y, x, y);

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

LRESULT CView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UpdateScrollBars();
	InvalidateRect(NULL);
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
		g.DrawImage(m_pPicture.get(), -m_scrollPosX, -m_scrollPosY);
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
//void CView::CenterImage(Gdiplus::Graphics& g, Gdiplus::Bitmap* image)
//{
//	CRect rc;
//	GetClientRect(&rc);
//
//	int imageWidth = image->GetWidth();
//	int imageHeight = image->GetHeight();
//
//	float scale = min((float)rc.Width() / imageWidth, (float)rc.Height() / imageHeight);
//	int scaledWidth = (int)(imageWidth * scale);
//	int scaledHeight = (int)(imageHeight * scale);
//
//	int x = (rc.Width() - scaledWidth) / 2;
//	int y = (rc.Height() - scaledHeight) / 2;
//
//	g.DrawImage(image, x, y, scaledWidth, scaledHeight);
//}


void CView::DrawLine(int x1, int y1, int x2, int y2)
{
	if (m_pPicture.get())
	{
		Graphics g(m_pPicture.get());
		Pen pen(m_drawColor, m_brushSize);
		g.DrawLine(&pen, x1, y1, x2, y2);
	}
}

void CView::NewPicture(int width, int height)
{
	m_pPicture.reset(new Bitmap(width, height, PixelFormat32bppARGB));

	Graphics g(m_pPicture.get());
	g.Clear(Color::White); 
	UpdateScrollBars();
	InvalidateRect(NULL);
}
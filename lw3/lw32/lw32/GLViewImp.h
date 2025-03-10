#pragma once

#include "OpenGL.h"

template <class T, class TBase = CWindow, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CGLViewImpl : public ATL::CWindowImpl<T, TBase, TWinTraits>
{
public:
	CGLViewImpl(bool needDepth = true, bool needStencil = false)
		: m_needDepth(needDepth) // ���������� ��������� ������ �����
		, m_needStencil(needStencil)
	{
	}

	DECLARE_WND_CLASS(NULL);

	// ������������ ������� ����������� ���������
	BEGIN_MSG_MAP(CGLViewImpl)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()
protected:
	// ������ ����� ������ ���� ���������� � �������-�����������
	virtual void DrawScene() = 0;

	virtual void AfterCreate()
	{
		// ������ �� ������ - ����� ����������� � ������ ����������
	}

	virtual void BeforeDestroy()
	{
		// ������ �� ������ - ����� ����������� � ������ ����������
	}

private:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(*this);

		// ���� OpenGL ��� ������������������, �� �������� ����� ��������� �����
		if (m_gl)
		{
			DrawScene();
			m_gl->SwapBuffers();
		}
		return 0;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// �������������� OpenGL
		m_gl.emplace(*this, m_needDepth, m_needStencil);
		AfterCreate();
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		BeforeDestroy();
		m_gl.reset();
		return 0;
	}

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// ������ �� ������, ������� ������� � ���, ��� �������
		// ���������� ������� ���� ���������
		return 0;
	}

private:
	std::optional<COpenGL> m_gl;
	bool m_needDepth;
	bool m_needStencil;
};
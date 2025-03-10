#include "StdAfx.h"
#include "OpenGL.h"

COpenGL::COpenGL(HWND hwnd, bool needDepth, bool needStencil)
	: m_dc(hwnd)
	, m_rc(NULL)
	, m_hwnd(hwnd)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd); 
	pfd.nVersion = 1; 
	pfd.dwFlags = PFD_SUPPORT_OPENGL | 
		PFD_DRAW_TO_WINDOW | 
		PFD_DOUBLEBUFFER | 
		PFD_GENERIC_ACCELERATED; 
	pfd.iPixelType = PFD_TYPE_RGBA; 
	pfd.cColorBits = 32; 
	pfd.cDepthBits = needDepth ? 24 : 0; 
	pfd.cStencilBits = needStencil ? 8 : 0; 

	int pixelFormat = m_dc.ChoosePixelFormat(&pfd);

	if (!pixelFormat)
	{
		Destroy();
		return;
	}

	if (!m_dc.SetPixelFormat(pixelFormat, &pfd))
	{
		Destroy();
		return;
	}

	m_rc = wglCreateContext(m_dc);
	if (m_rc)
	{
		if (!wglMakeCurrent(m_dc, m_rc))
		{
			Destroy();
		}
	}
}

COpenGL::~COpenGL(void)
{
	Destroy();
}

void COpenGL::Destroy(void)
{
	if (m_rc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_rc);
		m_rc = NULL;
	}

	if (m_dc)
	{
		::ReleaseDC(m_hwnd, m_dc.Detach());
	}
}

void COpenGL::SwapBuffers()
{
	if (m_dc && m_rc)
	{
		::SwapBuffers(m_dc);
	}
}
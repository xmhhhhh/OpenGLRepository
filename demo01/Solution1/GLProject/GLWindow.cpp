#include "GLWindow.h"
#include <GL/gl.h>
#include <GL/glu.h>


GLWindow::GLWindow()
{
	m_WindowPosX = 0;
	m_WindowPosY = 0;
	m_WindowWidth = 800;
	m_WindowHeight = 600;
	m_ScreenWidth = 1024;
	m_ScreenHeight = 768;
	m_BitsPerPixel = 32;

	m_IsFullScreen = false;
	m_hWnd = 0;
	m_hDC = 0;
	m_hRc = 0;
}


GLWindow::~GLWindow()
{
}


//创建窗口
bool GLWindow::Create(const char* window_title, bool full_screen, const char* class_name, HINSTANCE h_instance, LPVOID lpParam)
{
	m_IsFullScreen = full_screen;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_STEREO,
		PFD_TYPE_RGBA,
		m_BitsPerPixel,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	if (m_IsFullScreen == true)
	{
		if (ChangeScreenSetting() == false)
		{
			MessageBox(HWND_DESKTOP, "模式转换失败.\n在窗口模式下运行.", "Error", MB_OK | MB_ICONEXCLAMATION);
			m_IsFullScreen = false;
		}
		else
		{
			ShowCursor(false);
			windowStyle = WS_POPUP;
			windowExtendedStyle |= WS_EX_TOPMOST;
		}
	}

	RECT windowRect = {GetPosX(),GetPosY(),GetPosX()+GetWidth(),GetPosY()+GetHeight()};

	if (m_IsFullScreen == false)
	{
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);

		if (windowRect.left < 0)
		{
			windowRect.right -= windowRect.left;
			windowRect.left = 0;
		}
		if (windowRect.top < 0)
		{
			windowRect.bottom -= windowRect.top;
			windowRect.top = 0;
		}
	}

	m_hWnd = CreateWindowEx(windowExtendedStyle, class_name,
		window_title,
		windowStyle,
		windowRect.left, windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		HWND_DESKTOP,
		0,
		h_instance,
		lpParam);

	while (m_hWnd != 0)
	{
		m_hDC = GetDC(m_hWnd);
		if (m_hDC == 0)
		{
			break;
		}

		GLuint PixelFormat = ChoosePixelFormat(m_hDC,&pfd);

		if (PixelFormat == 0)
		{
			break;
		}

		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)
		{
			break;
		}

		m_hRc = wglCreateContext(m_hDC);

		if (m_hDC == 0)
		{
			break;

		}

		if (wglMakeCurrent(m_hDC,m_hRc) == false)
		{
			break;
		}

		ShowWindow(m_hWnd, SW_NORMAL);
		ReshapeGL();
		return true;
	}

	Destory();
	return false;
}

bool GLWindow::ChangeScreenSetting()
{
	DEVMODE dmScreenSettings;
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
	dmScreenSettings.dmSize = sizeof(DEVMODE);
	dmScreenSettings.dmPelsHeight = GetHeight();
	dmScreenSettings.dmPelsWidth = GetWidth();
	dmScreenSettings.dmBitsPerPel = m_BitsPerPixel;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;
	}

	return true;
}


void GLWindow::ReshapeGL()
{
	GLsizei width = GetWidth();
	GLsizei height = GetHeight();
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWindow::SetPosX(int x)
{
	m_WindowPosX = x;
}

void GLWindow::SetPosY(int y)
{
	m_WindowPosY = y;
}

int GLWindow::GetWidth()
{
	return m_WindowWidth;
}

int GLWindow::GetHeight()
{
	return m_WindowHeight;
}

void GLWindow::SetWidth(int width)
{
	m_WindowWidth = width;
}

void GLWindow::SetHeight(int height)
{
	m_WindowHeight = height;
}

int GLWindow::GetPosX()
{
	return m_WindowPosX;
}

int GLWindow::GetPosY()
{
	return m_WindowPosY;
}

void GLWindow::Destory()
{
	if (m_hWnd != 0)
	{
		if (m_hDC != 0)
		{
			wglMakeCurrent(m_hDC, 0);
			if (m_hDC != 0)
			{
				wglDeleteContext(m_hRc);
				m_hRc = 0;
			}
			ReleaseDC(m_hWnd, m_hDC);
			m_hDC = 0;

		}
		DestroyWindow(m_hWnd);
		m_hWnd = 0;
	}

	if(m_IsFullScreen)
	{ 
		ChangeDisplaySettings(NULL,0);
		ShowCursor(true);
	}
}




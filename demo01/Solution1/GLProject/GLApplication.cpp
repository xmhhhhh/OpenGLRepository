#include "GLApplication.h"
#include <winuser.h>


GLApplication::GLApplication(const char* class_name)
{
	m_ClassName = class_name;
	m_IsProgramLooping = true;
	m_CreateFullScreen = true;
	m_IsVisible = false;
	m_ResizeDraw = false;
	m_LastTickCount = 0;


}

GLApplication::GLApplication()
{
}



void GLApplication::ToggleFullscreen()
{
	PostMessage(m_Window, WM_TOGGLEFULLSCREEN, 0, 0);

}

void GLApplication::TerminateApplication()
{
	PostMessage(m_Window, WM_QUIT, 0, 0);
	m_IsProgramLooping = false;
}


LRESULT GLApplication::Message(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
			break;
		}
		break;

	case WM_CLOSE:
		TerminateApplication();
		return 0;
		break;
	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		m_LastTickCount = GetTickCount();
		return 0;
		break;
	case WM_PAINT:
		if (m_ResizeDraw == true)
		{
			m_Window.ReshapeGL();
			Draw();
			m_Window.SwapBuffers();
		}
		break;
	case WM_SIZING:
	{
		RECT* rect = (RECT*)lParam;
		m_Window.SetWidth(rect->right - rect->left);
		m_Window.SetHeight(rect->bottom-rect->top);
		return true;
	}
	break;
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_MINIMIZED:
			m_IsVisible = false;
			return 0;
			break;
		case SIZE_MAXIMIZED:
		case SIZE_RESTORED:
			m_IsVisible = true;
			m_Window.SetWidth(LOWORD(lParam));
			m_Window.SetHeight(HIWORD(lParam));
			m_Window.ReshapeGL();
			m_LastTickCount = GetTickCount();
			return 0;
			break;
		}
		break;

	case WM_KEYDOWN:
		m_Keys.SetPressed(wParam);
		return 0;
		break;
	case WM_KEYUP:
		m_Keys.SetReleased(wParam);
		return 0;
		break;
	case WM_TOGGLEFULLSCREEN:
		m_CreateFullScreen = !m_CreateFullScreen;
		PostMessage(hWnd, WM_QUIT, 0, 0);
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	int ret = -1;
	GLApplication * appl = GLApplication::Create("OpenGL");
	if (appl != 0)
	{
		ret = appl->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

		delete appl;
	}
	else
	{
		MessageBox(HWND_DESKTOP, "创建程序出错", "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	return ret;
}

LRESULT CALLBACK WindowProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG user_data = GetWindowLong(hWnd, GWLP_USERDATA);

	if (user_data == 0)
	{
		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT* creation = reinterpret_cast<CREATESTRUCT*>(lParam);

			GLApplication* appl = reinterpret_cast<GLApplication*>(creation->lpCreateParams);

			SetWindowLong(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(appl));

			appl->m_IsVisible = true;
			return 0;
		}
	}
	else
	{
		GLApplication* appl = reinterpret_cast<GLApplication*>(user_data);

		return appl->Message(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GLApplication::Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass,sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WindowProc1);
	windowClass.hInstance = hInstance;
	windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
	windowClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	windowClass.lpszClassName = m_ClassName;
	if(RegisterClassEx(&windowClass)==0)
	{
		MessageBox(HWND_DESKTOP,"注册窗口失败!","Error",MB_OK|MB_ICONEXCLAMATION);
		return -1;
	}

	if (MessageBox(HWND_DESKTOP, "您想在全屏模式下运行吗?", "是否全屏运行?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		m_CreateFullScreen = false;
	}

	while (m_IsProgramLooping)
	{
		if (m_Window.Create("OOGLFrame", m_CreateFullScreen, m_ClassName, hInstance, this) == true)
		{
				if (Init() == false)
			{
				TerminateApplication();
			}
			else
			{
				MSG msg;
				bool isMessagePumActive = true;
				m_LastTickCount = GetTickCount();
				m_Keys.Clear();
				while (isMessagePumActive == true)
				{
					if (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
					{
						if (msg.message != WM_QUIT)
						{
							DispatchMessage(&msg);
						}
						else
						{
							isMessagePumActive = false;
						}
					}
					else
					{
						if (m_IsVisible == false)
						{
							WaitMessage();
						}
						else
						{
							DWORD tickCount = GetTickCount();
							Update(tickCount-m_LastTickCount);
							m_LastTickCount = tickCount;
							Draw();
							m_Window.SwapBuffers();
						}
					}
				}
			}

			Uninit();
			m_Window.Destory();
		}
		else
		{
			MessageBox(HWND_DESKTOP,"创建OpenGL窗口错误","Error",MB_OK|MB_ICONEXCLAMATION);
			m_IsProgramLooping = false;
		}

	}

	UnregisterClass(m_ClassName, hInstance);
	return 0;
}




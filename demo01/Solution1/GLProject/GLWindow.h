#ifndef __GL_Window_H__
#define __GL_Window_H__

#include <windows.h>
class GLWindow
{
public:
	GLWindow();
	~GLWindow();
public:
	bool Create(const char* window_title, bool full_screen, const char* class_name, HINSTANCE h_instance, LPVOID lpParam);

	void Destory();

	bool ChangeScreenSetting();
	void ReshapeGL();
	void SwapBuffers()
	{
		::SwapBuffers(m_hDC);
	}
	void SetPosX(int x);
	void SetPosX(unsigned short x)
	{
		SetPosX((signed short)x);
	}
	void SetPosY(int y);
	void SetPosY(unsigned short y)
	{
		SetPosY((signed short)y);
	}
	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
	int GetPosX();
	int GetPosY();
	void SetHiColor() {
		m_BitsPerPixel = 16;
	};
	void SetTrueColor() {
		m_BitsPerPixel = 32;
	};

	operator HWND()
	{
		return m_hWnd;
	}


private:
	HWND m_hWnd;
	HDC m_hDC;
	HGLRC m_hRc;

	int m_WindowPosX;
	int m_WindowPosY;
	int m_WindowWidth;
	int m_WindowHeight;
	int m_ScreenWidth;
	int m_ScreenHeight;
	int m_BitsPerPixel;
	bool m_IsFullScreen;

};

#endif // !__GL_Window_H__





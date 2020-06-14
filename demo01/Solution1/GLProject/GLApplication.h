#ifndef __GL_APPLICATION_H__
#define __GL_APPLICATION_H__

#include "Keys.h"
#include "GLWindow.h"

class GLApplication
{
public:
	GLApplication();
	virtual ~GLApplication() {};

public:
	static GLApplication* Create(const char* class_name);

protected:
	virtual bool Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(DWORD millisceonds)=0;
	virtual void Draw() = 0;

	void ToggleFullscreen();
	void TerminateApplication();
	void ResizeDraw(bool enable) { m_ResizeDraw = enable; };

	Keys m_Keys;

	GLApplication(const char* class_name);

private:
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
	int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	friend LRESULT CALLBACK WindowProc1(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static const UINT WM_TOGGLEFULLSCREEN = (WM_USER + 1);

	GLWindow m_Window;

	const char* m_ClassName;

	bool m_IsProgramLooping;

	bool m_IsVisible;
	bool m_ResizeDraw;
	DWORD m_LastTickCount;

	bool m_CreateFullScreen;


	

};

#endif // !__GL_APPLICATION_H__





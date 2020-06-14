#include "UserExample.h"
#include <GL/gl.h>


UserExample::UserExample(const char* class_name) :GLApplication(class_name)
{
}


//GLApplication* GLApplication::Create(const char* class_name)
//{
//	UserExample* example = new UserExample(class_name);
//	return reinterpret_cast<GLApplication*>(example);
//}

bool UserExample::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	ResizeDraw(true);
	return true;
}

void UserExample::Uninit()
{
}

void UserExample::Update(DWORD milliseconds)
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)
	{
		TerminateApplication();
	}

	if (m_Keys.IsPressed(VK_F1) == true)
	{
		ToggleFullscreen();
	}

	m_Angle += (float)(milliseconds) / 15.0f;

	m_XOffset += (float)(milliseconds) / 10000.0f;

	m_YOffset += (float)(milliseconds) / 10000.0f;

}

void UserExample::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);

	glRotatef(m_Angle, 0.f, 1.f, 0.f);

	//glBegin(GL_TRIANGLES);

	//glColor3f(1.f, 0.f, 0.f);
	//glVertex3f(1.f, 0.f, 0.f);

	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(0.f, 1.f, 0.f);

	//glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(0.f, 0.f, -1.f);

	//glEnd();

	glBegin(GL_LINE);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);

	glEnd();

	//glBegin(GL_LINE);

	//glColor3f(0.f, 0.f, 0.f);
	//glVertex3f(0.f, 0.f, 0.f);

	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(0.f, 1.f, 0.f);

	//glEnd();

	//glBegin(GL_LINE);


	//glColor3f(0.f, 0.f, 0.f);
	//glVertex3f(0.f, 0.f, 0.f);

	//glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(0.f, 0.f, 1.f);

	//glEnd();


	glFlush();
}


UserExample::~UserExample()
{
}

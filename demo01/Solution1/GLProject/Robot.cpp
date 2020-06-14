#include "Robot.h"
#include <GL/gl.h>


Robot::Robot(const char* class_name):GLApplication(class_name)
{
}


Robot::~Robot()
{
}

GLApplication* GLApplication::Create(const char* class_name)
{
	Robot* example = new Robot(class_name);
	return reinterpret_cast<GLApplication*>(example);
}

bool Robot::Init()
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
void Robot::Uninit()
{
}

void Robot::DrawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glBegin(GL_POLYGON);

	/**顶面**/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	/**前面**/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);

	/**右面**/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	/**左面**/
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	/**底面**/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	/**后面**/
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);

	glEnd();

	glPopMatrix();
}

void Robot::DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 4.0f, 1.0f);
	DrawCube(0.0f, 0.0f,0.0f);

	glPopMatrix();
}

void Robot::DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(2.0f, 2.0f, 2.0f);
	DrawCube(0.0f, 0.0f, 0.0f);

	glPopMatrix();
}

void Robot::DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();

	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(3.0f, 5.0f, 2.0f);
	DrawCube(0.0f, 0.0f, 0.0f);

	glPopMatrix();
}

void Robot::DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);
	glScalef(1.0f, 5.0f, 1.0f);
	DrawCube(0.0f, 0.0f, 0.0f);

	glPopMatrix();
}

void Robot::DrawRobot(float xPos, float yPos, float zPos)
{
	static bool leg1 = true;
	static bool leg2 = false;

	static bool arm1 = true;
	static bool arm2 = false;

	glPushMatrix();

	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(xPos, yPos, zPos);
	DrawHead(1.0f, 2.0f, 0.0f);
	DrawTorso(1.5f, 0.0f, 0.0f);

	glPushMatrix();

	if (arm1)
		armAngle[0] = armAngle[0] + 0.1f;
	else
		armAngle[0] = armAngle[0] - 0.1f;

	if (armAngle[0] >= 15.0f)
		arm1 = false;

	if (armAngle[0] <= -15.0f)
		arm1 = true;

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);

	DrawArm(2.5f, 0.0f, -0.5f);

	glPopMatrix();

	glPushMatrix();

	if (arm2)
		armAngle[1] = armAngle[1] + 0.1f;
	else
		armAngle[1] = armAngle[1] - 0.1f;

	if (armAngle[1] >= 15.0f)
		arm2 = false;

	if (armAngle[1] <= -15.0f)
		arm2 = true;

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);

	DrawArm(-1.5f, 0.0f, -0.5f);

	glPopMatrix();

	glPushMatrix();

	if (leg1)
		legAngle[0] = legAngle[0] + 0.1f;
	else
		legAngle[0] = legAngle[0] - 0.1f;

	if (legAngle[0] >= 15.0f)
		leg1 = false;

	if (legAngle[0] <= -15.0f)
		leg1 = true;

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);

	DrawLeg(-0.5f,-5.0f, -0.5f);

	glPopMatrix();


	glPushMatrix();

	if (leg2)
		legAngle[1] = legAngle[1] + 0.1f;
	else
		legAngle[1] = legAngle[1] - 0.1f;

	if (legAngle[1] >= 15.0f)
		leg2 = false;

	if (legAngle[1] <= -15.0f)
		leg2 = true;

	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);

	DrawLeg(-1.5f, -5.0f, -0.5f);

	glPopMatrix();
}

void Robot::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -30.0f);
	glRotatef(angel, 0.0f, 1.0f, 0.0f);
	DrawRobot(0.0f, 0.0f, 0.0f);

	glPopMatrix();
	glFlush();
}

void Robot::Update(DWORD milliseconds)
{
	if(m_Keys.IsPressed(VK_ESCAPE)==true)
	{
		TerminateApplication();
	}

	if (m_Keys.IsPressed(VK_F1) == true)
	{
		ToggleFullscreen();
	}

	angel = angel + 0.05f;

	if(angel>=360.0f)
	{
		angel = 0.0f;
	}
}





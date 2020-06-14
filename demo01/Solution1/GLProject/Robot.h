#pragma once
#include "GLApplication.h"

class Robot:GLApplication
{
public:
	Robot();
	~Robot();
	bool Init() override;
	void Uninit() override;
	void Update(DWORD milliseconds) override;
	void Draw() override;
	void DrawRobot(float xPos,float yPos,float zPos);

private:
	void DrawHead(float xPos, float yPos, float zPos);
	void DrawTorso(float xPos, float yPos, float zPos);
	void DrawLeg(float xPos, float yPos, float zPos);
	void DrawArm(float xPos, float yPos, float zPos);
	void DrawCube(float xPos, float yPos, float zPos);


private:

	friend class GLApplication;
	Robot(const char* class_name);

	float angel;

	float legAngle[2];

	float armAngle[2];

};


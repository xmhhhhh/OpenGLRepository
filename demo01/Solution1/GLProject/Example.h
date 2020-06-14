#pragma once
#include "GLApplication.h"
class Example:GLApplication
{
public:
	bool Init() override;
	void Uninit() override;
	void Update(DWORD milliseconds) override;
	void Draw() override;


public:
	friend class GLApplication;
	Example(const char* class_name);

	float m_Angle;
	float m_XOffset;
	float m_YOffset;

};


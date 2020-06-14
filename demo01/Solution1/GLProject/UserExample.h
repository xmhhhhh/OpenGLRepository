#pragma once
#include "GLApplication.h"

class UserExample :GLApplication
{
public:
	bool Init() override;
	void Uninit() override;
	void Update(DWORD milliseconds) override;
	void Draw() override;

public:
public:
	friend class GLApplication;
	UserExample(const char* class_name);
	float m_Angle;
	float m_XOffset;
	float m_YOffset;
	~UserExample();
};


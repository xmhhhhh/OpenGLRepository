#ifndef __KEYS_H__
#define __KEYS_H__

#include <windows.h>
class Keys
{
public:
	Keys() { Clear(); };
	~Keys();

public:
	void Clear() { ZeroMemory(&m_KeyDown, sizeof(m_KeyDown)); };
	bool IsPressed(unsigned int key)
	{
		if (key < MAX_KEYS)
		{
			return m_KeyDown[key] == true;
		}
		return false;
	};
	void SetPressed(unsigned int key)
	{
		if (key < MAX_KEYS)
		{
			m_KeyDown[key] = true;
		}
	};
	void SetReleased(unsigned int key)
	{
		if (key < MAX_KEYS)
		{
			m_KeyDown[key] = false;
		}
	};


private:
	static const unsigned int MAX_KEYS = 256;
	bool m_KeyDown[MAX_KEYS];
};


#endif // !__KEYS_H__





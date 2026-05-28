#pragma once
#include "Define.h"
class CKeyMgr
{

private:
	CKeyMgr();
	CKeyMgr(const CKeyMgr& rhs) = delete;
	CKeyMgr& operator = (CKeyMgr& rCLineMgr) = delete;
	~CKeyMgr();

public:
	bool KeyPressing(int iKey);
	bool KeyUp(int iKey);
	bool KeyDown(int iKey);
	void KeyUpdate();

public:
	static CKeyMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CKeyMgr* m_pInstance;

	bool	m_bPrevState[VK_MAX];
	bool	m_bCurState[VK_MAX];
};


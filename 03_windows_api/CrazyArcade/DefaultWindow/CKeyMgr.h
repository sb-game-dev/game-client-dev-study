#pragma once
#include "Define.h"
class CKeyMgr
{
public:
	CKeyMgr();
	CKeyMgr(const CKeyMgr* rhs) = delete;
	CKeyMgr& operator=(const CKeyMgr* rhs) = delete;
	~CKeyMgr();

public :
	bool	KeyPressing(int iKey);
	bool	KeyUp(int iKey);
	bool	KeyDown(int iKey);
	void	KeyUpdate();
public:
	static CKeyMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CKeyMgr* m_pInstance;

	bool m_bCurState[VK_MAX];
	bool m_bPreState[VK_MAX];
};


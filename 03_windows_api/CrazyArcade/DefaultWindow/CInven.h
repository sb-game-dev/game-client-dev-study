#pragma once
#include "Define.h"

class CInven
{
public:
	CInven();
	CInven(const CInven* rhs) = delete;
	CInven& operator=(const CInven* rhs) = delete;
	~CInven();

public:
	void	SetGold(int iGold) { m_iGold += iGold; }


	int		GetGold() { return m_iGold; }

public:
	static CInven* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CInven;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CInven*	m_pInstance;
	int				m_iGold;


};


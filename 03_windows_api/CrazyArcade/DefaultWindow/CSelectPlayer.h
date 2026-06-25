#pragma once
#include "Define.h"

class CSelectPlayer
{
public:
	CSelectPlayer();
	CSelectPlayer(const CSelectPlayer* rhs) = delete;
	CSelectPlayer& operator=(const CSelectPlayer* rhs) = delete;
	~CSelectPlayer();

public:
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();


public:
	void	SetDraw(bool bDraw) { m_bDraw = bDraw; }

	bool	GetDraw() { return m_bDraw; }

public:
	static CSelectPlayer* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CSelectPlayer;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CSelectPlayer* m_pInstance;

	bool	m_bDraw;
};


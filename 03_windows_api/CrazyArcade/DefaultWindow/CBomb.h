#pragma once
#include "CObj.h"
class CBomb
	:public CObj
{
public:
	CBomb();
	virtual~CBomb();
public:
	void		Initialize()		override;
	int			Update()			override;
	void		LateUpdate()		override;
	void		Render(HDC hDC)		override;
	void		Release()			override;

public:
	void		SetBombRange(int iBombRange) { m_iBombRange = iBombRange; }
	void		SetPlayerCollision() { m_bPlayerCollision = true; }
	bool		GetPlayerCollision() { return m_bPlayerCollision; }
	CObj*		CreateWave();

private:
	ULONGLONG		m_dwBombTime;
	int				m_iBombRange;
	bool			m_bPlayerCollision;
};


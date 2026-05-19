#pragma once
#include "Define.h"
class CObj
{
public :
	CObj();
	~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int	 Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	void UpdateRect();

	void TakeDamage(int iNum)			{ m_tStat.fHp -= iNum; }
	void SetPos(float fX, float fY)		{ m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetDead(bool bDead)			{ m_bDead = bDead; }
	void SetDir(DIRECTION eDir)			{ m_eDir = eDir; }

	INFO GetInfo() { return m_tInfo; }
	RECT* GetRect() { return &m_tRect; }
	STAT GetStat() { return m_tStat; }


protected:
	INFO m_tInfo;
	RECT m_tRect;
	
	STAT m_tStat;
	DIRECTION m_eDir;

	float m_fSpeed;
	bool m_bDead;
};


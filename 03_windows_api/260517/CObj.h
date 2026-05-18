#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public :
	virtual void Initialize()	PURE;
	virtual bool Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	void SetPos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}

	void TakeDamage(int iNum) { m_tStat.fHp -= iNum; }
	void SetStat(STAT tStat) { m_tStat = tStat; }
	void SetDir(DIRECTION eDIR) { m_eDIR = eDIR; }
	void SetDead(bool bDead) { m_bDead = bDead; }

	INFO GetInfo() { return m_tInfo; }
	RECT* GetRect() { return &m_tRect; }
	STAT GetStat() { return m_tStat; }


	void UpdateRect();
protected:
	INFO m_tInfo;
	RECT m_tRect;

	STAT m_tStat;

	float m_fSpeed;

	DIRECTION m_eDIR;
	bool m_bDead;
};


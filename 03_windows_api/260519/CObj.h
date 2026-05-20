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
	void SetDead()			{ m_bDead = DEAD; }
	void SetDir(float fRadian)			{ m_fRadian = fRadian; }

	const INFO GetInfo()const { return m_tInfo; }
	const RECT* GetRect()const { return &m_tRect; }
	const STAT GetStat()const { return m_tStat; }


protected:
	INFO m_tInfo;
	RECT m_tRect;
	
	STAT m_tStat;
	float m_fRadian;

	float m_fSpeed;
	bool m_bDead;
};


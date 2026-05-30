#pragma once
#include "Define.h"
class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual void Initialize()	PURE;
	virtual int Update()		PURE;
	virtual void LateUpdate()	PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()		PURE;

public:
	INFO GetInfo() { return m_tInfo; }
	RECT* GetRect() { return &m_tRect; }
	STAT GetStat() { return m_tStat; }
	
	void AdjustPos(float fX, float fY) { m_tInfo.fX = ((int)fX / 40) * 40.f + 20; m_tInfo.fY = ((int)fY / 40) * 40.f + 20; };

	void SetDir(DIRECTION eDir) { m_eDir = eDir; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetStat(float fHp, float fAttack) { m_tStat.fHp = fHp; m_tStat.fAttack = fAttack; }
	void SetDead() { m_bDead = DEAD; }
	void SetPosX(float fNum) { m_tInfo.fX += fNum; }
	void SetPosY(float fNum) { m_tInfo.fY += fNum; }

	void TakeDamage(float fDamage) { m_tStat.fHp -= fDamage; }
	void UpdateRect();

protected:
	INFO m_tInfo;
	RECT m_tRect;
	STAT m_tStat;

	float m_fSpeed;
	bool m_bDead;
	DIRECTION m_eDir;
};


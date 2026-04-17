#pragma once
#include "Define.h"
class CPlayer
{
private:
	CPlayer();
	~CPlayer();
	enum JOBINDEX
	{
		WARRIOR = 1,
		MAGE,
		THEIF
	};
public:
	void Initialize();
	void Update();
	void Release();
	static CPlayer* Create();
	void Destroy();

	void Render()const;

	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	Info GetInfo() {return m_tInfo;}

	void Heal(int iNum) {m_tInfo.iHp = iNum;}
private:
	Info m_tInfo;
};


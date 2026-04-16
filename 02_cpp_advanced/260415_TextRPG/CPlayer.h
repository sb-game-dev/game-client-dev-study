#pragma once
#include "Define.h"
class CPlayer
{
private:
	enum JOBINDEX
	{
		WARRIOR = 1,
		MAGE,
		THEIF,
		LOADDATA
	};
private:
	CPlayer();
	~CPlayer();
public:
	void Initialize();
	void Update();
	void Release();
	void Render() const;
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	Info GetInfo() { return m_tInfo; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
public:
	static CPlayer* Create();
	void Destroy();

private:
	Info m_tInfo;
};


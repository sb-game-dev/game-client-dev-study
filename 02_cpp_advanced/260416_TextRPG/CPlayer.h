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
public:
	static CPlayer* Create();
	void Destroy();
	void Render() const;
	Info GetInfo() const { return m_tInfo; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
private:
	Info m_tInfo;
};


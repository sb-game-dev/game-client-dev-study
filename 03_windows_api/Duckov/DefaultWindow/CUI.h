#pragma once
#include "Define.h"
#include "CPlayer.h"
class CUI
{
public:
	CUI();
	~CUI();

public:
	void Initialize();
	void Update();
	void Render(HDC hDC);

public:
	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	void SetAmmoInfo(AMMOINFO eAmmoInfo) { m_tAmmoInfo = eAmmoInfo; }
private:
	CPlayer* m_pPlayer;

	RECT m_rcMainWeapon;
	RECT m_rcSubWeapon;
	RECT m_rcHeal;

	AMMOINFO m_tAmmoInfo;
};


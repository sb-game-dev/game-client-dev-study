#pragma once

#include "CObj.h"

class CPlayer : public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize()       override;
    int  Update()           override;
    void LateUpdate()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

    PLAYERCOVER GetCoverL() { return m_eCoverL; }
    PLAYERCOVER GetCoverR() { return m_eCoverR; }

private:
    void        KeyInput();
    void        Move();
    void        ChangeWeapon();
    void        Shoot();

private:
    void        RenderInven(HDC hDC);
    void        UpdateRect(RECT& m_WeaponRect, INFO& m_WeaponInfo);

private:
    CObj* CreateBullet();

private:
    WEAPON m_eWEAPON;

    INFO m_InfoMainWeapon;
    INFO m_InfoSubWeapon;
    INFO m_InfoHeal;
    INFO m_InfoSelect;

    RECT m_rcMainWeapon;
    RECT m_rcSubWeapon;
    RECT m_rcHeal;
    RECT m_rcSelect;

    PLAYERCOVER m_eCoverL;
    PLAYERCOVER m_eCoverR;
};


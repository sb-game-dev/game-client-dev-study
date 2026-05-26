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

    WEAPON      GetWeapon() { return m_eWEAPON; }
    AMMOINFO    GetAmmoInfo() { return m_tAmmoInfo; }
    bool        GetReload() { return m_bReload; }
private:
    void        KeyInput();
    void        Move();
    void        ChangeWeapon();
    void        Shoot();
    void        Reload();
    void        Heal();
private:
    void        RenderInven(HDC hDC);
    void        UpdateRect(RECT& m_WeaponRect, INFO& m_WeaponInfo);

private:
    CObj* CreateBullet(float fAngle = 0);

private:
    WEAPON m_eWEAPON;

    //INFO m_InfoMainWeapon;
    //INFO m_InfoSubWeapon;
    //INFO m_InfoHeal;
    //INFO m_InfoSelect;
    //
    //RECT m_rcMainWeapon;
    //RECT m_rcSubWeapon;
    //RECT m_rcHeal;
    //RECT m_rcSelect;

    RECT m_rcHpBar;

    PLAYERCOVER m_eCoverL;
    PLAYERCOVER m_eCoverR;

    //int m_iCurMain;
    //int m_iReserveMain;
    //
    //int m_iCurSub;
    //int m_iReserveSub;

    AMMOINFO m_tAmmoInfo;

    bool m_bReload;
    DWORD m_dwTime;
};


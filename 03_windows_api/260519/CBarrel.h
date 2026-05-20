#pragma once
#include "CObj.h"
class CPlayer;
class CBarrel :
    public CObj
{
public :
    CBarrel();
    virtual ~CBarrel();

public :

    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
    void SetMouse(CObj* pMouse) { m_pMouse = pMouse; }
    float GetRadian() { return m_fRadian; }

private:
    CObj* m_pPlayer;
    CObj* m_pMouse;

    DWORD dwTime;
};


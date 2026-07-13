#pragma once
#include "CObj.h"
class CShield :
    public CObj
{
public:
    CShield();
    virtual~CShield();
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

    void            GetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }


    CObj*           m_pPlayer;
};


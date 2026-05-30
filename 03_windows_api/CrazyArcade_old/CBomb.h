#pragma once
#include "CObj.h"
class CBomb :
    public CObj
{
public:
    CBomb();
    ~CBomb();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;


public:
    STATE GetState() { return m_eState; }
    void SetState(STATE eState) { m_eState = eState; }
private:
    DWORD m_dwTime;
    STATE m_eState;

};


#pragma once
#include "CObj.h"
class CBlock :
    public CObj
{
public:
    CBlock();
    ~CBlock();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;


public:
    void        SetMove(DIRECTION eDIR);
    void        Move();


private:
    void        CreateItem();
private:
    bool        m_bMove;
    float       m_fDstX;
    float       m_fDstY;
};


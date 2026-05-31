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

    void        SetType(BLOCK_TYPE eBT) { m_eBT = eBT; }
    BLOCK_TYPE  GetBT() { return m_eBT; }

private:
    void        CreateItem();
private:
    bool        m_bMove;
    float       m_fDstX;
    float       m_fDstY;
    BLOCK_TYPE  m_eBT;
};


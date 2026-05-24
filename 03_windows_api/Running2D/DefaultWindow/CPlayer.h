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

private:
    void        KeyInput();

    POINT m_Point1;
    POINT m_Point2;
};


#pragma once
#include "CObj.h"
class CMouse :
    public CObj
{
public:
    CMouse();
    ~CMouse();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void RenderMain(HDC hDC);
    void RenderSub(HDC hDC);
    void RenderReload(HDC hDC);

private:
    int m_iSize;
    POINT m_tPoint;
};


#pragma once
#include "CObj.h"
class CObstacle :
    public CObj
{
public:
    CObstacle();
    ~CObstacle();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    float m_time;
    float m_fPrevX;
    float m_fPrevY;
};


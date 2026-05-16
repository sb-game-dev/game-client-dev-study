#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
public:
    CBullet(const char& key);
    ~CBullet();

public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    bool CheckColiision();
private:
    float m_fXSpeed;
    float m_fYSpeed;
};


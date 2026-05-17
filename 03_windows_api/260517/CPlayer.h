#pragma once
#include "CObj.h"
#include "CBullet.h"
class CPlayer :
    public CObj
{
public:
    CPlayer();
    ~CPlayer();

public:
    // CObj을(를) 통해 상속됨
    void Initialize()       override;
    void Update()           override;
    void Render(HDC hDC)    override;
    void Release()          override;

public:
    void SetBullet(list<CObj*>* pBulletList) { m_BulletListP = pBulletList; }

private:
    void KeyDown();
    CObj* CreateBullet(const char& key);

private:
    list<CObj*>* m_BulletListP;
};


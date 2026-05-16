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
    void Initialize()       override;
    void Update()           override;
    void Render(HDC hDC)    override;
    void Release()          override;

    void SetBullet(list<CObj*>* pBulletList) { m_BulletListP = pBulletList; }
private:
    void KeyInput();
    CObj* CreateBullet(const char& key);
private:
    list<CObj*>* m_BulletListP;
};


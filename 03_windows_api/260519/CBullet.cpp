#include "pch.h"
#include "CBullet.h"
#include "CFollowMgr.h"
#include "CObjMgr.h"
CBullet::CBullet()
{
}

CBullet::~CBullet()
{
    Release();
}

void CBullet::Initialize()
{
    m_tInfo.fCX = 30;
    m_tInfo.fCY = 30;

    m_tStat.fAttack = 1000;
    m_tStat.fHp = 1;

    m_fSpeed = 5.f;
}

int CBullet::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
    CObj* pNearestObj = nullptr;
    float fMinDistance = 1000.f;
    for (auto& pObj : CObjMgr::GetInstance()->GetList(OBJ_MONSTER))
    {
        float fDeltaX = abs(pObj->GetInfo().fX - m_tInfo.fX);
        float fDeltaY = abs(pObj->GetInfo().fY - m_tInfo.fY);
        float fDistance = sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);
        if (fMinDistance >= fDistance)
        {
            fMinDistance = fDistance;
            pNearestObj = pObj;
        }
    }
    if(pNearestObj != nullptr)
        CFollowMgr::Follow(pNearestObj->GetInfo(), m_tInfo, m_fSpeed);
    else
        return DEAD;

    return NONEVENT;
}

void CBullet::LateUpdate()
{
    if (m_tInfo.fX <= 0 || m_tInfo.fX >= WINCX || m_tInfo.fY <= 0 || m_tInfo.fY >= WINCY)
        m_bDead = DEAD;
    if (m_tStat.fHp <= 0)
        m_bDead = DEAD;
}

void CBullet::Render(HDC hDC)
{
    Ellipse(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void CBullet::Release()
{
}

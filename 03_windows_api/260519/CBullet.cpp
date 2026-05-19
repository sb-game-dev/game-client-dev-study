#include "pch.h"
#include "CBullet.h"

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

    m_fSpeed = 20.f;
}

int CBullet::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
    switch (m_eDir)
    {
    case DIR_LEFT:
        m_tInfo.fX -= m_fSpeed;
        break;
    case DIR_TOP:
        m_tInfo.fY -= m_fSpeed;
        break;
    case DIR_RIGHT:
        m_tInfo.fX += m_fSpeed;
        break;
    case DIR_BOTTOM:
        m_tInfo.fY += m_fSpeed;
        break;
    case DIR_LU:
        m_tInfo.fY -= m_fSpeed;
        m_tInfo.fX -= m_fSpeed;
        break;
    case DIR_RU:
        m_tInfo.fY -= m_fSpeed;
        m_tInfo.fX += m_fSpeed;
        break;
    default:
        break;
    }
    __super::UpdateRect();
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

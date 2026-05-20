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
    m_tInfo.fX += m_fSpeed * cos(m_fRadian);
    m_tInfo.fY -= m_fSpeed * sin(m_fRadian);

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

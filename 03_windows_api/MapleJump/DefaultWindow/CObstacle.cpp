#include "pch.h"
#include "CObstacle.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
CObstacle::CObstacle():m_time(0.f), m_fPrevX(0.f), m_fPrevY(0.f)
{
}

CObstacle::~CObstacle()
{
    Release();
}

void CObstacle::Initialize()
{
    m_tInfo.fCX = 20.f;
    m_tInfo.fCY = 20.f;
}

int CObstacle::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
    m_fPrevX = m_tInfo.fX;
    m_fPrevY = m_tInfo.fY;
    m_time += 0.1f;
    m_tInfo.fY += 0.5f * 9.8f * m_time * m_time;
    return 0;
}

void CObstacle::LateUpdate()
{
    if (CLineMgr::GetInstance()->SetLine(m_tInfo.fX,m_tInfo.fY,m_fPrevX,m_fPrevY))
        m_bDead = DEAD;
}

void CObstacle::Render(HDC hDC)
{
    float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
    Ellipse(hDC,
        m_tRect.left + fScrollX,
        m_tRect.top,
        m_tRect.right + fScrollX,
        m_tRect.bottom);
}

void CObstacle::Release()
{
}

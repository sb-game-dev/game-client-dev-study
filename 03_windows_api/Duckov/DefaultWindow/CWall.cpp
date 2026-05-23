#include "pch.h"
#include "CWall.h"

CWall::CWall()
{
}

CWall::~CWall()
{
    Release();
}

void CWall::Initialize()
{
    m_tInfo.fCX = 20.f;
    m_tInfo.fCY = 20.f;
}

int CWall::Update()
{
    if (m_bDead == DEAD)
        return DEAD;
    return NONEVENT;
}

void CWall::LateUpdate()
{
    if (m_tAbility.fHp <= 0)
        m_bDead = DEAD;
}

void CWall::Render(HDC hDC)
{
    Rectangle(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void CWall::Release()
{
}

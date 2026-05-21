#include "pch.h"
#include "CMonster.h"
#include "CObjMgr.h"
#include "CFollowMgr.h"
#include "CCollisionMgr.h"
CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{
    m_tInfo.fCX = 50.f;
    m_tInfo.fCY = 50.f;

    m_tStat.fAttack = 10;
    m_tStat.fHp = 10;
    m_fSpeed = 1.f;
}

int CMonster::Update()
{
    if (m_bDead == DEAD)
        return DEAD;


    return NONEVENT;
}

void CMonster::LateUpdate()
{
    //if (m_tInfo.fX <= 0 || m_tInfo.fX >= WINCX)
    //    m_fSpeed *= -1;
    if (m_tStat.fHp <= 0)
        m_bDead = DEAD;
    if (!CCollisionMgr::CheckCircle(CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front(), this))
        CFollowMgr::Follow(CObjMgr::GetInstance()->GetList(OBJ_PLAYER).front()->GetInfo(), m_tInfo, m_fSpeed);
}

void CMonster::Render(HDC hDC)
{
    Rectangle(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);

}

void CMonster::Release()
{
}

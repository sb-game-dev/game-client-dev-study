#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
CPlayer::CPlayer():m_iBombPower(2), m_iMaxBomb(2)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),40.f,40.f };
	m_tStat = { 100.f,10.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	KeyDown();
	return NONEVENT;
}

void CPlayer::LateUpdate()
{
	if (m_tStat.fHp <= 0)
		m_bDead = DEAD;
	for (auto& Bomb : CObjMgr::GetInstance()->GetList(OBJ_BOMB))
	{
		if (dynamic_cast<CBomb*> (Bomb)->GetState() == ST_EXPLODE_READY)
		{
			bool bRunning = true;

			dynamic_cast<CBomb*> (Bomb)->SetState(ST_EXPLODE_ING);
			float fX = Bomb->GetInfo().fX;
			float fY = Bomb->GetInfo().fY;
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				if (!bRunning) break;
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX + Bomb->GetInfo().fCX * i, fY, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
				for (auto& pObj : CObjMgr::GetInstance()->GetList(OBJ_MONSTER))
				{
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY - pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						break;
					}
					if (fabsf(pBomb->GetInfo().fX + 40.f - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY - pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						if (i < m_iBombPower)
						{
							CObj* pBomb = CAbstractFactory<CBomb>::Create(fX + Bomb->GetInfo().fCX * (i + 1), fY, 1, 1000);
							dynamic_cast<CBomb*>(pBomb)->SetState(ST_EXPLODE_ING);
							CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
						}
						break;
					}
				}
			}
			bRunning = true;
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				if (!bRunning) break;
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX - Bomb->GetInfo().fCX * i, fY, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
				for (auto& pObj : CObjMgr::GetInstance()->GetList(OBJ_MONSTER))
				{
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY - pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						break;
					}
					if (fabsf(pBomb->GetInfo().fX - 40.f - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY - pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						if (i < m_iBombPower)
						{
							CObj* pBomb = CAbstractFactory<CBomb>::Create(fX - Bomb->GetInfo().fCX * (i + 1), fY, 1, 1000);
							dynamic_cast<CBomb*>(pBomb)->SetState(ST_EXPLODE_ING);
							CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
						}
						break;
					}
				}
			}
			bRunning = true;
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				if (!bRunning) break;
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY + Bomb->GetInfo().fCX * i, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
				for (auto& pObj : CObjMgr::GetInstance()->GetList(OBJ_MONSTER))
				{
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY- pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						break;
					}
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX)<=0.1f
						&& fabsf(pBomb->GetInfo().fY + 40.f - pObj->GetInfo().fY)<=0.1f)
					{
						bRunning = false;
						if (i < m_iBombPower)
						{
							CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY + Bomb->GetInfo().fCX * (i + 1), 1, 1000);
							dynamic_cast<CBomb*>(pBomb)->SetState(ST_EXPLODE_ING);
							CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
						}
						break;
					}
				}
			}
			bRunning = true;
			for (int i = 1; i <= m_iBombPower; ++i)
			{
				if (!bRunning) break;
				CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY - Bomb->GetInfo().fCX * i, 1, 1000);
				dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
				CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
				for (auto& pObj : CObjMgr::GetInstance()->GetList(OBJ_MONSTER))
				{
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY  - pObj->GetInfo().fY) <= 0.1f)
					{
						bRunning = false;
						break;
					}
					if (fabsf(pBomb->GetInfo().fX - pObj->GetInfo().fX) <= 0.1f
						&& fabsf(pBomb->GetInfo().fY - 40.f - pObj->GetInfo().fY) <= 0.1f)
					{
						if(i < m_iBombPower)
						{
							CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY - Bomb->GetInfo().fCX * (i + 1), 1, 1000);
							dynamic_cast<CBomb*> (pBomb)->SetState(ST_EXPLODE_ING);
							CObjMgr::GetInstance()->AddObject(OBJ_BOMB, pBomb);
						}
						bRunning = false;
						break;
					}
				}
			}
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::KeyDown()
{
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
	if (GetAsyncKeyState(VK_SPACE) & 0x001)
		if(CObjMgr::GetInstance()->GetList(OBJ_BOMB).size()< m_iMaxBomb)
			CObjMgr::GetInstance()->AddObject(OBJ_BOMB, CreateBomb());
}

CObj* CPlayer::CreateBomb()
{
	CObj* pBomb = CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY, 1, 1000);

	pBomb->AdjustPos(m_tInfo.fX, m_tInfo.fY);
	return pBomb;
}



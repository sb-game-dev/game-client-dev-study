#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CBomb.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CBmpMgr.h"
CPlayer::CPlayer() :m_iBombRange(2), m_iBombMax(2)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"../Image/크레이지 아케이드 리소스/Resource/Player/player_Down.bmp", L"Player");
	m_tInfo = { (WINCX >> 1),(WINCY >> 1),70.f,70.f };
	m_fSpeed = 3.f;
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
	
}

void CPlayer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::GetInstance()->FindImage(L"Player");
	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(0, 255, 0));
}

void CPlayer::Release()
{
}

void CPlayer::KeyDown()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	else if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
		if (CObjMgr::GetInstance()->GetList(OBJ_BOMB).size() < m_iBombMax)
			CObjMgr::GetInstance()->AddObject(OBJ_BOMB, CreateBomb());
}

CObj* CPlayer::CreateBomb()
{
	CObj* pBomb = CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY);

	pBomb->AdjustPos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBomb*>(pBomb)->SetBombRange(m_iBombRange);
	return pBomb;
}



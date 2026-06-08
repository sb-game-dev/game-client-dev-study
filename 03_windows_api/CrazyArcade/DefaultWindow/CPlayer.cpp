#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CImgMgr.h"
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_down.png", L"player_down");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_up.png", L"player_up");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_left.png", L"player_left");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Player/player_right.png", L"player_right");
	m_tInfo = { float(WINCX >> 1), float(WINCY >> 1), 40.f, 40.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	KeyInput();

	return NOEVENT;
}


void CPlayer::LateUpdate()
{
}

void CPlayer::Render(Graphics* _pGraphics)
{
	
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (CKeyMgr::GetInstance()->KeyPressing(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (CKeyMgr::GetInstance()->KeyPressing(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (CKeyMgr::GetInstance()->KeyPressing(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (CKeyMgr::GetInstance()->KeyPressing(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

}


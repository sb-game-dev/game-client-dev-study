#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer() 
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
	m_tInfo.vPos += m_tInfo.vDir;
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		m_tInfo.vPos.x - 50.f, 
		m_tInfo.vPos.y - 50.f,
		m_tInfo.vPos.x + 50.f,
		m_tInfo.vPos.y + 50.f);
}

void CPlayer::Release()
{
}




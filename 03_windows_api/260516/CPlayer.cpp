#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX >> 1 , WINCY >> 1 , 100,100 };
	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
	KeyInput();
	__super::UpdateRect();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom
	);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState('W'))
		m_BulletListP->push_back(CreateBullet('W'));
	if (GetAsyncKeyState('A'))
		m_BulletListP->push_back(CreateBullet('A'));
	if (GetAsyncKeyState('S'))
		m_BulletListP->push_back(CreateBullet('S'));
	if (GetAsyncKeyState('D'))
		m_BulletListP->push_back(CreateBullet('D'));
	if (GetAsyncKeyState('Q'))
		m_BulletListP->push_back(CreateBullet('Q'));
	if (GetAsyncKeyState('E'))
		m_BulletListP->push_back(CreateBullet('E'));
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_BulletListP->push_back(CreateBullet('W'));
		m_BulletListP->push_back(CreateBullet('Q'));
		m_BulletListP->push_back(CreateBullet('E'));
	}

}

CObj* CPlayer::CreateBullet(const char& key)
{
	CObj* pBullet = new CBullet(key);

	pBullet->Initialize();
	pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

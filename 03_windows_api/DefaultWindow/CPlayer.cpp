#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer():m_BulletList(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { float(WINCX >> 1),float(WINCY >> 1),100.f,100.f };
	m_fSpeed = 10.f;
}

void CPlayer::Update()
{
	KeyInput();

	__super::UpdateRect(); //상속 관계에서 최상위 클래스를 지칭하는 지시자
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_BulletList->push_back(CreateBullet());
		m_BulletList->push_back(CreateBullet('A'));
		m_BulletList->push_back(CreateBullet('D'));
	}
	if (GetAsyncKeyState('W') & 0x8000)
		m_BulletList->push_back(CreateBullet());
	if (GetAsyncKeyState('A') & 0x8000)
		m_BulletList->push_back(CreateBullet('A'));
	if (GetAsyncKeyState('D') & 0x8000)
		m_BulletList->push_back(CreateBullet('D'));
}

CObj* CPlayer::CreateBullet()
{
	CObj* pBullet = new CBullet;

	pBullet->Initialize();
	pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

CObj* CPlayer::CreateBullet(const char& key)
{
	CObj* pBullet = new CBullet(key);

	pBullet->Initialize();
	pBullet->SetPos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

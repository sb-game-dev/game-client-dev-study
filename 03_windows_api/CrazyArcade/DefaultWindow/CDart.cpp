#include "pch.h"
#include "CDart.h"
#include "CBmpMgr.h"

CDart::CDart()
{
}

CDart::~CDart()
{
	Release();
}

void CDart::Initialize()
{
	m_tInfo.fCX = 27.f;
	m_tInfo.fCY = 9.f;

	m_fSpeed = 010;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = 27;
	m_tFrame.iCY = 9;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eRenderID = GAMEOBJECT;
}

int CDart::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	switch (m_eDIR)
	{
	case DIR_UP:
		m_tFrame.iStart = 54;
		m_tInfo.fCX = 9.f;
		m_tInfo.fCY = 27.f;
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_DOWN:
		m_tFrame.iStart = 63;
		m_tInfo.fCX = 9.f;
		m_tInfo.fCY = 27.f;
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR_LEFT:
		m_tFrame.iStart = 27;
		m_tInfo.fCX = 27.f;
		m_tInfo.fCY = 9.f;
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tFrame.iStart = 0;
		m_tInfo.fCX = 27.f;
		m_tInfo.fCY = 9.f;
		m_tInfo.fX += m_fSpeed;
		break;
	default:
		break;
	}
	return NOEVENT;
}

void CDart::LateUpdate()
{
	if (!CheckInMap(m_tInfo.fX, m_tInfo.fY))
	{
		m_bDead = DEAD;
	}
}

void CDart::Render(HDC hDC)
{
	if (m_bDead == DEAD)
		return;

	HDC hDart = CBmpMgr::GetInstance()->FindImage(L"dart_obj");

	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tRect.left),	// 목적지 LEFT, TOP
		int(m_tRect.top),
		m_tInfo.fCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tInfo.fCY,
		hDart,						// 원본 이미지 DC
		m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tInfo.fCX,			// 원본 이미지 가로, 세로 사이즈
		m_tInfo.fCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CDart::Release()
{
}

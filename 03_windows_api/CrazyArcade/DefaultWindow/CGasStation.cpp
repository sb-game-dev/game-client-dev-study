#include "pch.h"
#include "CGasStation.h"
#include "CBmpMgr.h"
CGasStation::CGasStation():m_bRefuel(false)
{
}

CGasStation::~CGasStation()
{
}

void CGasStation::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.iCX = 80;
	m_tFrame.iCY = 83;
	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.bLoop = true;
	m_tFrame.dwSpeed = 100.f;
}

int CGasStation::Update()
{
	return 0;
}

void CGasStation::LateUpdate()
{
	if (m_bRefuel)
	{
		MoveFrame();
	}
	else
	{
		m_tFrame.iStart = 0;
	}
}

void CGasStation::Render(HDC hDC)
{
	HDC hGasStation = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 목적지 DC
		220,	// 목적지 LEFT, TOP
		118,
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hGasStation,						// 원본 이미지 DC
		m_tFrame.iStart * m_tFrame.iCX,							// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,				// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CGasStation::Release()
{
}

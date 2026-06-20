#include "pch.h"
#include "CBase.h"
#include "CBmpMgr.h"

CBase::CBase():m_bBaseMoveFrame(false)
{
}

CBase::~CBase()
{
	Release();
}

void CBase::Initialize()
{
	m_eRenderID = BACKGROUND;

	if (!lstrcmp(L"tile_final", m_pFrameKey) || !lstrcmp(L"tile_start", m_pFrameKey))
		m_tInfo.fCY = 80.f;
	else
		m_tInfo.fCY = 40.f;

	m_tInfo.fCX = 40.f;
	m_tFrame.iStart = 1;
	m_tFrame.iEnd = 3;
	m_tFrame.iCX = m_tInfo.fCX;
	m_tFrame.iCY = m_tInfo.fCY;
	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwSpeed = 200.f;
}

int CBase::Update()
{
	if (m_bBaseMoveFrame)
	{
		BaseMoveFrame();
	}
	else
	{
		m_tFrame.iStart = 0;
	}

	return 0;
}

void CBase::LateUpdate()
{

}

void CBase::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;
	HDC hBase = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	BitBlt(hDC,							// 목적지 DC
		m_tRect.left,					// 목적지 LEFT,RIGHT
		m_tRect.top,
		(int)m_tInfo.fCX,				// 원본 DC에서 가져올 영역의 크기
		(int)m_tInfo.fCY,
		hBase,							// 원본 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력
}

void CBase::Release()
{
}

void CBase::BaseMoveFrame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed <= GetTickCount64())
	{
		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iStart <= 1)
			m_tFrame.iStart = 2;
		else
			m_tFrame.iStart = 1;
	}
}

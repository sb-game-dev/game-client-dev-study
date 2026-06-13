#include "pch.h"
#include "CMonster.h"
#include "CBmpMgr.h"

CMonster::CMonster():m_ePreMotion(MOTION_END), m_eCurMotion(START), m_dwFrameCount(GetTickCount64())
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 2.f;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = 40;
	m_tFrame.iCY = 40;
	m_tFrame.dwSpeed = 150.f;
	m_tFrame.dwTime = GetTickCount64();

	m_eRenderID = GAMEOBJECT;
}

int CMonster::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	MoveFrame(); 
	CheckFrame();
	return 0;
}

void CMonster::LateUpdate()
{

}

void CMonster::Render(HDC hDC)
{
	HDC hMonster = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hMonster,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,	// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(0, 255, 0));		// 제거할 픽셀 색상
}

void CMonster::Release()
{
}

void CMonster::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case IDLE:
		m_pFrameKey = L"Bean_Monster_Down";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.bLoop = false;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LEFT:
		m_pFrameKey = L"Bean_Monster_Left";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case RIGHT:
		m_pFrameKey = L"Bean_Monster_Right";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case UP:
		m_pFrameKey = L"Bean_Monster_Up";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case DOWN:
		m_pFrameKey = L"Bean_Monster_Down";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case HIT:
		m_pFrameKey = L"Bean_Monster_Death";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 3;
		m_tFrame.bLoop = false;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case MOTION_END:
		break;
	default:
		break;
	}
	m_ePreMotion = m_eCurMotion;
}

void CMonster::CheckFrame()
{
	if (m_eCurMotion == START
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = IDLE;
		ChangeMotion();
	}
	else if (m_eCurMotion == HIT
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}
#include "pch.h"
#include "CBoss.h"
#include "CImgMgr.h"

CBoss::CBoss():m_eCurMotion(IDLE), m_iHP(20)
{
}

CBoss::~CBoss()
{
    Release();
}

void CBoss::Initialize()
{
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_down.png", L"Boss_down");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_up.png", L"Boss_up");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_left.png", L"Boss_left");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_right.png", L"Boss_right");

	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_AttackDown.png", L"Boss_AttackDown");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_AttackUp.png", L"Boss_AttackUp");
	//CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_AttackLeft.png", L"Boss_AttackLeft");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_AttackRight.png", L"Boss_right");

	
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_HitDown.png", L"Boss_HitDown");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_HitLeft.png", L"Boss_HitLeft");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_HitRight.png", L"Boss_HitRight");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_HitUp.png", L"Boss_HitUp");

	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_Bubble.png", L"Boss_Bubble");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/Boss/Boss_Dead.png", L"Boss_Dead");


	CImgMgr::GetInstance()->InsertImg(L"../Resource/UI/HP_Bar.png", L"HP_Bar");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/UI/HP_Bar_Blue.png", L"HP_Bar_Blue");
	CImgMgr::GetInstance()->InsertImg(L"../Resource/UI/HP_Bar_Red.png", L"HP_Bar_Red");

	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	m_fSpeed = 5.f;

	m_eCurMotion = IDLE;

	//m_pFrameKey = L"Boss_down";
	//m_tFrame.iStart = 0;
	//m_tFrame.iEnd = 1;
	//m_tFrame.iMotion = 0;
	//m_tFrame.bLoop = false;
	//m_tFrame.iCX = 132;
	//m_tFrame.iCY = 172;
	//m_tFrame.dwSpeed = 100.f;
	//m_tFrame.dwTime = GetTickCount64();
}

int CBoss::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	MoveFrame();
	CheckFrame();
	ChangeMotion();
    return 0;
}

void CBoss::LateUpdate()
{
	
}

void CBoss::Render(HDC hDC)
{
	Graphics* _pGraphics = Graphics::FromHDC(hDC);

	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);

	if (m_iHP > 0)
	{
		Gdiplus::Image* pHpBar = CImgMgr::GetInstance()->FindImg(L"HP_Bar");
		Rect rectHpBar = {
		   int(m_tInfo.fX - (43)),
		   int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 20,
		   86,
		   11 };

		_pGraphics->DrawImage(pHpBar, rectHpBar,
			0, 0,
			86, 11,
			UnitPixel);

		Gdiplus::Image* pHpBarBlue = CImgMgr::GetInstance()->FindImg(L"HP_Bar_Blue");
		Rect rectHpBarBlue = {
		   int(m_tInfo.fX - (41)),
		   int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 18,
		   int(82 * m_iHP / 20),7 };
		_pGraphics->DrawImage(pHpBarBlue, rectHpBarBlue,
			0, 0,
			82, 7,
			UnitPixel);
	}

	Rect rect = { 
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,
		m_tFrame.iCY };
	_pGraphics->DrawImage(pImg, rect,
		m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
		m_tFrame.iCX, m_tFrame.iCY,
		UnitPixel);
}

void CBoss::Release()
{
}
void CBoss::SetHit()
{
	if (m_eCurMotion != HIT)
	{
		m_iHP-=5;
		if (m_iHP <= 0)
			m_eCurMotion = BUBBLE;
		else
			m_eCurMotion = HIT;
		ChangeMotion();
	}
}
void CBoss::ChangeMotion()
{
	if (m_ePreMotion == m_eCurMotion)
		return;
	switch (m_eCurMotion)
	{
	case IDLE:
		m_pFrameKey = L"Boss_down";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 172;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LEFT:
		m_pFrameKey = L"Boss_left";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 171;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case RIGHT:
		m_pFrameKey = L"Boss_right";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 172;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case UP:
		m_pFrameKey = L"Boss_up";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 173;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case DOWN:
		m_pFrameKey = L"Boss_down";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 8;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 172;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case HIT:
		m_pFrameKey = L"Boss_HitDown";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 170;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case BUBBLE:
		m_pFrameKey = L"Boss_Bubble";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 120;
		m_tFrame.iCY = 122;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case DEATH:
		m_pFrameKey = L"Boss_Dead";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 133;
		m_tFrame.iCY = 172;
		m_tFrame.dwSpeed = 100.f;
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

void CBoss::CheckFrame()
{
	if (m_eCurMotion == HIT
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = IDLE;
		ChangeMotion();
	}
	if (m_eCurMotion == BUBBLE
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_eCurMotion = DEATH;
		ChangeMotion();
	}
	if (m_eCurMotion == DEATH
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}
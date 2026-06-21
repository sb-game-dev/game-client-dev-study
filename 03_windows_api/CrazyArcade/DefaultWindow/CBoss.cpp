#include "pch.h"
#include "CBoss.h"
#include "CImgMgr.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CWave.h"
#include "CBomb.h"

CBoss::CBoss():m_eCurMotion(IDLE), m_iHP(20), m_dwAttackTime(GetTickCount64()),
m_iAttackRange(2), m_iAttackRangeDelta(1), m_bMoveAttack(false), m_iShootCnt(0),
m_bCheckRemainTile(true), m_iRemainTile(195), m_fAngrySpeed(4.f),m_fWalkSpeed(1.f)
{
	m_ePreMotion = MOTION_END;
	m_eCurMotion = IDLE;
	m_eReturnMotion = IDLE;
}

CBoss::~CBoss()
{
    Release();
}

void CBoss::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	m_fSpeed = m_fWalkSpeed;

	m_eCurMotion = IDLE;
	
	CreateDst();
}

int CBoss::Update()
{
	if (m_bDead == DEAD)
		return DEAD;

	if (CObjMgr::GetInstance()->GetList(OBJ_PLAYER).empty())
	{
		m_eCurMotion = DOWN;
		ChangeMotion();
		return 0;
	}
	BossPattern();
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
	//Graphics* _pGraphics = Graphics::FromHDC(hDC);
#ifdef _DEBUG
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
#endif // _DEBUG


	HDC hBoss = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,					// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,			// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hBoss,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,							// 원본 이미지 LEFT, TOP
		m_tFrame.iMotion,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
	if (m_iHP > 0)
	{
		HDC hHpBar = CBmpMgr::GetInstance()->FindImage(L"HP_Bar");
		GdiTransparentBlt(hDC,					// 목적지 DC
			int(m_tInfo.fX - (43)),	
			int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 8,
			86,			// 목적지 공간의 가로, 세로 사이즈
			11,
			hHpBar,						// 원본 이미지 DC
			0,0,
			86,11,
			RGB(255, 0, 255));		// 제거할 픽셀 색상
		//Gdiplus::Image* pHpBar = CImgMgr::GetInstance()->FindImg(L"HP_Bar");
		//Rect rectHpBar = {
		//   int(m_tInfo.fX - (43)),
		//   int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 20,
		//   86,
		//   11 };
		//
		//_pGraphics->DrawImage(pHpBar, rectHpBar,
		//	0, 0,
		//	86, 11,
		//	UnitPixel);
		HDC hHpBarColor = NULL;
		if (m_iHP > 5)
			hHpBarColor = CBmpMgr::GetInstance()->FindImage(L"HP_Bar_Blue");
		else
		{
			//m_fSpeed = m_fAngrySpeed;
			hHpBarColor = CBmpMgr::GetInstance()->FindImage(L"HP_Bar_Red");
		}
		GdiTransparentBlt(hDC,					// 목적지 DC
			int(m_tInfo.fX - (41)),
			int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 6,
			int(82 * m_iHP / 20), 7,
			hHpBarColor,						// 원본 이미지 DC
			0, 0,
			int(82 * m_iHP / 20), 7,
			RGB(255, 0, 255));		// 제거할 픽셀 색상
		//Gdiplus::Image* pHpBarBlue = CImgMgr::GetInstance()->FindImg(L"HP_Bar_Blue");
		//Rect rectHpBarBlue = {
		//   int(m_tInfo.fX - (41)),
		//   int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)) - 18,
		//   int(82 * m_iHP / 20),7 };
		//_pGraphics->DrawImage(pHpBarBlue, rectHpBarBlue,
		//	0, 0,
		//	82, 7,
		//	UnitPixel);
	}

	//Gdiplus::Image* pImg = CImgMgr::GetInstance()->FindImg(m_pFrameKey);
	//Rect rect = { 
	//	int(m_tInfo.fX - (m_tFrame.iCX / 2)),
	//	int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
	//	m_tFrame.iCX,
	//	m_tFrame.iCY };
	//_pGraphics->DrawImage(pImg, rect,
	//	m_tFrame.iCX * m_tFrame.iStart, m_tFrame.iCY * m_tFrame.iMotion,
	//	m_tFrame.iCX, m_tFrame.iCY,
	//	UnitPixel);
}

void CBoss::Release()
{

}
void CBoss::SetHit()
{
	if (m_eCurMotion != HIT)
	{
		m_iHP -= 1;
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
		m_tFrame.iCY = 172;
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
		m_tFrame.iCY = 172;
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
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 170;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 170;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		break;
	case ATTACK:
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 5;
		m_tFrame.iMotion = 340;
		m_tFrame.bLoop = true;
		m_tFrame.iCX = 132;
		m_tFrame.iCY = 175;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_dwFrameCount = GetTickCount64();
		m_dwAttackTime = GetTickCount64();
		break;
	case BUBBLE:
		m_pFrameKey = L"Boss_Bubble";
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 15;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 120;
		m_tFrame.iCY = 122;
		m_tFrame.dwSpeed = 150.f;
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
		m_eCurMotion = m_eReturnMotion;
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

void CBoss::BossAttackAround(int iRange)
{
	int iBossX = AdjustPosX(m_tInfo.fX);
	int iBossY = AdjustPosY(m_tInfo.fY);

	for (int j = iBossY - iRange*40; j <= iBossY + iRange * 40; j+=40)
	{
		if (j == iBossY - iRange * 40 || j == iBossY + iRange * 40)
		{
			for (int i = iBossX - iRange * 40; i <= iBossX + iRange * 40; i+=40)
			{
				if(CheckInMap(i,j))
					CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(i, j, L"WaveCenter"));
			}
		}
		else
		{
			if(CheckInMap(iBossX - iRange * 40, j))
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(iBossX - iRange * 40, j, L"WaveCenter"));
			if (CheckInMap(iBossX + iRange * 40, j))
			CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(iBossX + iRange * 40, j, L"WaveCenter"));
		}
	}

}

void CBoss::CreateDst()
{
	srand(unsigned(time(NULL)));
	int x = (rand() % 7) + 4;
	int y = (rand() % 5) + 4;

	m_fDstX = x * 40 + 40;
	m_fDstY = y * 40 + 60;
}

void CBoss::BossPattern()
{
	if (m_eCurMotion == BUBBLE || m_eCurMotion == DEATH || m_eCurMotion == HIT)
		return;
	if (m_bMoveAttack == true)
	{
		if (m_iRemainTile > 0)
			AttackPattern1();//RangeAttack
		else
			AttackPattern2();//Shoot
	}
	else
	{
		Move();
	}
}
void CBoss::Move()
{
	if (m_tInfo.fX < m_fDstX)
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurMotion = RIGHT;
		m_eReturnMotion = RIGHT;
	}
	else if (m_tInfo.fX > m_fDstX)
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurMotion = LEFT;
		m_eReturnMotion = LEFT;
	}
	else if (m_tInfo.fY < m_fDstY)
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurMotion = DOWN;
		m_eReturnMotion = DOWN;
	}
	else if (m_tInfo.fY > m_fDstY)
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurMotion = UP;
		m_eReturnMotion = UP;
	}
	else
	{
		m_bMoveAttack = true;
		if (m_bCheckRemainTile == true)
		{
			m_iRemainTile = CObjMgr::GetInstance()->GetRemainTile();
			//cout << "TileCnt: " << m_iRemainTile << endl;
			if (m_iRemainTile == 0)
				m_bCheckRemainTile = false;
		}
	}
	ChangeMotion();
}
void CBoss::AttackPattern1()
{
	m_eReturnMotion = DOWN;
	m_pFrameKey = L"Boss_down";
	if (m_dwAttackTime + 2000 <= GetTickCount64())
	{
		m_eCurMotion = ATTACK;
		m_dwAttackTime = GetTickCount64();
		++m_iAttackRange;
		BossAttackAround(m_iAttackRange);
		if (m_iAttackRange > 5)
		{
			CreateDst();
			m_iAttackRange = 2;
			m_bMoveAttack = false;
		}
	}
}

void CBoss::AttackPattern2()
{
	int iHalfX = (MAP_LEFT + MAP_RIGHT) / 2;
	int iHalfY = (MAP_TOP + MAP_BOTTOM) / 2;
	if (m_tInfo.fX > iHalfX && m_tInfo.fY < iHalfY)//1사분면
	{
		m_eReturnMotion = LEFT;
		m_pFrameKey = L"Boss_left";
		m_eCurMotion = ATTACK;
		if (m_dwAttackTime + 700 <= GetTickCount64())
		{
			m_dwAttackTime = GetTickCount64();
			CreateBomb(m_tInfo.fX - 80, m_tInfo.fY, DIR_LEFT);
			++m_iShootCnt;
		}
	}
	else if (m_tInfo.fX <= iHalfX && m_tInfo.fY < iHalfY)//2사분면
	{
		m_eReturnMotion = DOWN;
		m_pFrameKey = L"Boss_down";
		m_eCurMotion = ATTACK;
		if (m_dwAttackTime + 700 <= GetTickCount64())
		{
			m_dwAttackTime = GetTickCount64();
			CreateBomb(m_tInfo.fX, m_tInfo.fY + 80, DIR_DOWN);
			++m_iShootCnt;
		}
	}
	else if (m_tInfo.fX > iHalfX && m_tInfo.fY >= iHalfY)//3사분면
	{
		m_eReturnMotion = RIGHT;
		m_pFrameKey = L"Boss_right";
		m_eCurMotion = ATTACK;
		if (m_dwAttackTime + 700 <= GetTickCount64())
		{
			m_dwAttackTime = GetTickCount64();
			CreateBomb(m_tInfo.fX + 80, m_tInfo.fY, DIR_RIGHT);
			++m_iShootCnt;
		}
	}
	else//4사분면 + 나머지
	{
		m_eReturnMotion = UP;
		m_pFrameKey = L"Boss_up";
		m_eCurMotion = ATTACK;
		if (m_dwAttackTime + 700 <= GetTickCount64())
		{
			m_dwAttackTime = GetTickCount64();
			CreateBomb(m_tInfo.fX, m_tInfo.fY - 80, DIR_UP);
			++m_iShootCnt;
		}
	}
	if (m_iShootCnt >= 3)
	{
		CreateDst();
		m_iShootCnt = 0;
		m_bMoveAttack = false;
	}
}

void CBoss::CreateBomb(float fX, float fY,DIRECTION eDir)
{
	CObj* pBomb = CAbstractFactory<CBomb>::Create(fX, fY, L"RainbowBubble");
	pBomb->SetCanMove(true);
	pBomb->SetDirection(eDir);
	dynamic_cast<CBomb*>(pBomb)->SetPlayerCollision();
	dynamic_cast<CBomb*>(pBomb)->SetBombRange(3);
	CObjMgr::GetInstance()->AddObject(OBJ_BOSS_BOMB, pBomb);
}

#include "pch.h"
#include "CMonster.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"

CMonster::CMonster():m_ePreMotion(MOTION_END), m_eCurMotion(START), m_dwFrameCount(GetTickCount64()), m_pTile(nullptr), m_pBombList(nullptr),
m_fDstX(0.f), m_fDstY(0.f), m_pBombList2(nullptr), m_bMonsterWin(false), m_eMonsterType(MONSTERTYPE_END)
{

}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_pTile = CObjMgr::GetInstance()->GetTilePtr();
	m_pBombList  = CObjMgr::GetInstance()->GetListPtr(OBJ_BOMB);
	m_pBombList2 = CObjMgr::GetInstance()->GetListPtr(OBJ_BOMB2);

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	if (!lstrcmp(m_pFrameKey, L"Bean_Monster_Start"))
	{
		m_eMonsterType = BEAN1;
	}
	else if (!lstrcmp(m_pFrameKey, L"Bean_Monster_Start2"))
	{
		m_eMonsterType = BEAN2;
	}
	
	m_fSpeed = 0.f;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = 40;
	m_tFrame.iCY = 40;
	m_tFrame.dwSpeed = 150.f;
	m_tFrame.dwTime = GetTickCount64();
	m_ePreMotion = MOTION_END;
	m_eCurMotion = START;
	m_bCanMove = false;
	ChangeMotion();
}

int CMonster::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	if ((CObjMgr::GetInstance()->GetRemainPlayer() == false && CObjMgr::GetInstance()->GetRemainPlayer2() == false) || m_bMonsterWin)
	{
		m_eCurMotion = DOWN;
		ChangeMotion();
		return 0;
	}
	if (m_bCanMove == true)
	{
		switch (m_eCurMotion)
		{
		case UP:
			if (m_fDstY != m_tInfo.fY)
				m_tInfo.fY -= m_fSpeed;
			else
				m_bCanMove = false;
			break;
		case LEFT:
			if (m_fDstX != m_tInfo.fX)
				m_tInfo.fX -= m_fSpeed;
			else
				m_bCanMove = false;
			break;
		case DOWN:
			if (m_fDstY != m_tInfo.fY)
				m_tInfo.fY += m_fSpeed;
			else
				m_bCanMove = false;
			break;
		case RIGHT:
			if (m_fDstX != m_tInfo.fX)
				m_tInfo.fX += m_fSpeed;
			else
				m_bCanMove = false;
			break;
		default:
			break;
		}
	}
	else
	{
		if(m_eCurMotion == LEFT ||
			m_eCurMotion == RIGHT||
			m_eCurMotion == UP||
			m_eCurMotion == DOWN)
		LeftHandRuleMove();
	}
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
	
	GdiTransparentBlt(hDC,						// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX / 2)),	// 목적지 LEFT, TOP
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,							// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hMonster,								// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,			// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,							// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(0, 255, 0));						// 제거할 픽셀 색상
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
	case START:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Down";
		else if (m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Down2";
		m_fSpeed = 0.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 4;
		m_tFrame.iMotion = 0;
		m_tFrame.bLoop = false;
		m_tFrame.iCX = 40;
		m_tFrame.iCY = 40;
		m_tFrame.dwSpeed = 150.f;
		m_tFrame.dwTime = GetTickCount64();
		m_ePreMotion = MOTION_END;
		m_eCurMotion = START;
		m_bCanMove = false;
		break;
	case IDLE:
		if(m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Down";
		else if(m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Down2";
		m_fSpeed = 0;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 1;
		m_tFrame.bLoop = false;
		m_tFrame.dwSpeed = 300.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case LEFT:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Left";
		else if(m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Left2";

		m_fSpeed = 2.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case RIGHT:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Right";
		else if (m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Right2";

		m_fSpeed = 2.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case UP:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Up";
		else if (m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Up2";
		m_fSpeed = 2.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case DOWN:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Down";
		else if (m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Down2";
		m_fSpeed = 2.f;
		m_tFrame.iStart = 0;
		m_tFrame.iEnd = 2;
		m_tFrame.bLoop = true;
		m_tFrame.dwSpeed = 100.f;
		m_tFrame.dwTime = GetTickCount64();
		break;
	case HIT:
		if (m_eMonsterType == BEAN1)
			m_pFrameKey = L"Bean_Monster_Death";
		else if (m_eMonsterType == BEAN2)
			m_pFrameKey = L"Bean_Monster_Death2";
		m_fSpeed = 0.f;
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
	if ((m_eCurMotion == START )
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_fSpeed = 2.f;
		m_eCurMotion = LEFT;
		ChangeMotion();
	}
	else if (m_eCurMotion == HIT
		&& m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}



void CMonster::LeftHandRuleMove()
{
	int x = ((m_tInfo.fX) - MAP_LEFT) / TILECX;
	int y = ((m_tInfo.fY) - MAP_TOP) / TILECX;

	int Left	= 0;
	int Front	= 0;
	int Right	= 0;
	int Back	= 0;

	int LeftIndex = y * MAP_CNT_X + x - 1;
	if (LeftIndex < 0 || LeftIndex / MAP_CNT_X != (LeftIndex + 1) / MAP_CNT_X)
	{
		LeftIndex = -1;
	}
	int TopIndex = (y - 1) * MAP_CNT_X + x;

	if (TopIndex < 0)
	{
		TopIndex = -1;
	}
	int RightIndex = y * MAP_CNT_X + x + 1;

	if (RightIndex / MAP_CNT_X != (RightIndex - 1) / MAP_CNT_X)
	{
		RightIndex = -1;
	}
	int BottomIndex = (y + 1) * MAP_CNT_X + x;

	if (BottomIndex > 194)
	{
		BottomIndex = -1;
	}
	
	switch (m_eCurMotion)
	{
	case LEFT:
		Left = BottomIndex;
		Front = LeftIndex;
		Right = TopIndex;
		Back = RightIndex;
		break;
	case RIGHT:
		Left = TopIndex;
		Front = RightIndex;
		Right = BottomIndex;
		Back = LeftIndex;
		break;
	case UP:
		Left = LeftIndex;
		Front = TopIndex;
		Right = RightIndex;
		Back = BottomIndex;
		break;
	case DOWN:
		Left = RightIndex;
		Front = BottomIndex;
		Right = LeftIndex;
		Back = TopIndex;
		break;
	default:
		break;
	}
	
	if (Left != -1 && ((*m_pTile)[Left]->GetFrame().iStart < 2 || ((*m_pTile)[Left]->GetFrame().iStart >=11 && (*m_pTile)[Left]->GetFrame().iStart <=17)))
	{
		bool iBombCheck = true;
		x = (Left % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		y = (Left / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		for (auto& pBomb : *(m_pBombList))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		for (auto& pBomb : *(m_pBombList2))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		if (iBombCheck == true)
		{
			SetDestination(DIR_LEFT, Left);
			return;
		}
	}
	// 앞쪽 확인
	if (Front != -1 && ((*m_pTile)[Front]->GetFrame().iStart < 2 || ((*m_pTile)[Front]->GetFrame().iStart >= 11 && (*m_pTile)[Front]->GetFrame().iStart <= 17)))
	{
		bool iBombCheck = true;
		x = (Front % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		y = (Front / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		for (auto& pBomb : *(m_pBombList))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		for (auto& pBomb : *(m_pBombList2))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		if (iBombCheck == true)
		{
			SetDestination(DIR_UP, Front);
			return;
		}
	}
	// 오른쪽 확인
	if (Right != -1 && ((*m_pTile)[Right]->GetFrame().iStart < 2 || ((*m_pTile)[Right]->GetFrame().iStart >= 11 && (*m_pTile)[Right]->GetFrame().iStart <= 17)))
	{
		bool iBombCheck = true;
		x = (Right % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		y = (Right / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		for (auto& pBomb : *(m_pBombList))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		for (auto& pBomb : *(m_pBombList2))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		if (iBombCheck == true)
		{
			SetDestination(DIR_RIGHT, Right);
			return;
			
		}
	}
	//	뒤쪽 확인
	if (Back != -1 && ((*m_pTile)[Back]->GetFrame().iStart < 2 || ((*m_pTile)[Back]->GetFrame().iStart >= 11 && (*m_pTile)[Back]->GetFrame().iStart <= 17)))
	{
		bool iBombCheck = true;
		x = (Back % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		y = (Back / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		for (auto& pBomb : *(m_pBombList))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		for (auto& pBomb : *(m_pBombList2))
		{
			if (pBomb->GetInfo()->fX == x && pBomb->GetInfo()->fY == y)
			{
				iBombCheck = false;
				break;
			}
		}
		if (iBombCheck == true)
		{
			SetDestination(DIR_DOWN, Back);
			return;
		}
	}
}

void CMonster::SetDestination(DIRECTION eDir, int iIndex)
{
	switch (eDir)
	{
	case DIR_UP:
		m_fDstX = (iIndex % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		m_fDstY = (iIndex / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		m_bCanMove = true;
		break;
	case DIR_DOWN:
		m_fDstX = (iIndex % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		m_fDstY = (iIndex / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		m_eCurMotion = MOTION((m_eCurMotion - 2 + 2) % 4 + 2);
		m_bCanMove = true;
		break;
	case DIR_LEFT:
		m_fDstX = (iIndex % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		m_fDstY = (iIndex / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		m_eCurMotion = MOTION((m_eCurMotion - 2 + 1) % 4 + 2);
		m_bCanMove = true;
		break;
	case DIR_RIGHT:
		m_fDstX = (iIndex % MAP_CNT_X) * 40 + 20 + MAP_LEFT;
		m_fDstY = (iIndex / MAP_CNT_X) * 40 + 20 + MAP_TOP;
		m_eCurMotion = MOTION((m_eCurMotion - 2 + 3) % 4 + 2);
		m_bCanMove = true;
		break;
	default:
		break;
	}
	ChangeMotion();
}

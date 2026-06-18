#include "pch.h"
#include "CWave.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CWave::CWave():m_dwFrameCount(GetTickCount64())
{
}

CWave::~CWave()
{
	Release();
}

void CWave::Initialize()
{
	m_eRenderID = GAMEOBJECT;

	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 35.f;

	m_fSpeed = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.bLoop = false;
	m_tFrame.iCX = 40;
	m_tFrame.iCY = 40;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();
}

int CWave::Update()
{
	if (m_bDead == DEAD)
		return DEAD;
	MoveFrame();
	CheckFrame();
	return 0;
}

void CWave::LateUpdate()
{
}

void CWave::Render(HDC hDC)
{
	HDC hTile = CBmpMgr::GetInstance()->FindImage(m_pFrameKey);
	GdiTransparentBlt(hDC,			// 목적지 DC
		int(m_tInfo.fX - (m_tFrame.iCX * 0.5)),
		int(m_tInfo.fY - (m_tFrame.iCY - m_tInfo.fCY * 0.5)),
		m_tFrame.iCX,				// 목적지 공간의 가로, 세로 사이즈
		m_tFrame.iCY,
		hTile,						// 원본 이미지 DC
		m_tFrame.iCX * m_tFrame.iStart,// 원본 이미지 LEFT, TOP
		0,
		m_tFrame.iCX,			// 원본 이미지 가로, 세로 사이즈
		m_tFrame.iCY,
		RGB(255, 0, 255));		// 제거할 픽셀 색상
}

void CWave::Release()
{
}

void CWave::CheckFrame()
{
	if (m_dwFrameCount + m_tFrame.dwSpeed * m_tFrame.iEnd <= GetTickCount64())
	{
		m_bDead = DEAD;
	}
}

void CWave::Spread(int iBombRange)
{
	vector<CObj*> tempTileVec = CObjMgr::GetInstance()->GetTile();
	int x = (m_tInfo.fX - MAP_LEFT) / TILECX;
	int y = (m_tInfo.fY - MAP_TOP) / TILECX;
	for (int i = 1; i <= iBombRange; ++i)
	{
		int RightIndex = y * MAP_CNT_X + x + i;
		if (RightIndex/ MAP_CNT_X != (RightIndex-1) / MAP_CNT_X)
			break;
		if (tempTileVec[RightIndex]->GetFrame().iStart <= 1||
			(tempTileVec[RightIndex]->GetFrame().iStart >= 11 && tempTileVec[RightIndex]->GetFrame().iStart<=17))
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right"));
		}
		else if (tempTileVec[RightIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX + m_tInfo.fCX * i, m_tInfo.fY, L"right"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int LeftIndex = y * MAP_CNT_X + x - i;
		if (LeftIndex<0 ||LeftIndex / MAP_CNT_X != (LeftIndex + 1) / MAP_CNT_X)
			break;
		if (tempTileVec[LeftIndex]->GetFrame().iStart <= 1||
			(tempTileVec[LeftIndex]->GetFrame().iStart >= 11 && tempTileVec[LeftIndex]->GetFrame().iStart <= 17))
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left"));
		}
		else if (tempTileVec[LeftIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX - m_tInfo.fCX * i, m_tInfo.fY , L"left"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int TopIndex = (y - i) * MAP_CNT_X + x;
		if (TopIndex < 0)
			break;
		if (tempTileVec[TopIndex]->GetFrame().iStart <= 1 ||
			(tempTileVec[TopIndex]->GetFrame().iStart >= 11 && tempTileVec[TopIndex]->GetFrame().iStart <= 17))
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up"));
		}
		else if (tempTileVec[TopIndex]->GetFrame().iStart <= 3)
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY * i, L"up"));
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= iBombRange; ++i)
	{
		int BottomIndex = (y + i) * MAP_CNT_X + x;
		if (BottomIndex > 194)
			return;
		if (tempTileVec[BottomIndex]->GetFrame().iStart <= 1 ||
			(tempTileVec[BottomIndex]->GetFrame().iStart >= 11 && tempTileVec[BottomIndex]->GetFrame().iStart <= 17))
		{
			if (i == iBombRange)
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down_end"));

			else
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down"));
		}																										   
		else if (tempTileVec[BottomIndex]->GetFrame().iStart <= 3)													   
		{																										   
			if (i == iBombRange)																				   
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down_end"));
																												   
			else																								   
				CObjMgr::GetInstance()->AddObject(OBJ_WAVE, CAbstractFactory<CWave>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * i, L"down"));
			break;
		}
		else
			break;
	}
}

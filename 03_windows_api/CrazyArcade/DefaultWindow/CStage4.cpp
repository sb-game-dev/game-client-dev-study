#include "pch.h"
#include "CStage4.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CImgMgr.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "CItem.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CButton.h"
#include "CMark.h"
#include "CInven.h"
CStage4::CStage4():m_iFirstBlockCnt(0),m_hBackGround(NULL),m_pMarkList(nullptr), m_bFristBlockCheck(false),m_pTileVector(nullptr), m_iClearRangeCnt(0), m_pPlayer(nullptr)
{
	ZeroMemory(&m_bBlockCheck, sizeof(m_bBlockCheck));

	ZeroMemory(&m_iBlockCnt, sizeof(m_iBlockCnt));
	m_BlockRect[0][0] = { 0,0,3,4 };
	m_BlockRect[0][1] = { 0,0,5,2 };

	m_BlockRect[1][0] = { 5,0,9,2 };
	m_BlockRect[1][1] = { 5,0,9,2 };

	m_BlockRect[2][0] = { 9,0,11,2 };
	m_BlockRect[2][1] = { 11,0,14,4 };

	m_BlockRect[3][0] = { 3,2,7,4 };
	m_BlockRect[3][1] = { 3,4,5,6 };

	m_BlockRect[4][0] = { 7,2,11,4 };
	m_BlockRect[4][1] = { 9,4,11,6 };

	m_BlockRect[5][0] = { 0,4,3,6 };
	m_BlockRect[5][1] = { 0,4,3,6 };

	m_BlockRect[6][0] = { 5,4,9,6 };
	m_BlockRect[6][1] = { 6,6,8,7 };

	m_BlockRect[7][0] = { 11,4,14,6 };
	m_BlockRect[7][1] = { 11,4,14,6};

	m_BlockRect[8][0] = { 0,6,2,10 };
	m_BlockRect[8][1] = { 0,6,2,10 };

	m_BlockRect[9][0] = { 2,6,4,8 };
	m_BlockRect[9][1] = { 2,6,4,8 };

	m_BlockRect[10][0] = { 4,6,6,9 };
	m_BlockRect[10][1] = { 6,7,7,9 };

	m_BlockRect[11][0] = { 7,6,10,9 };
	m_BlockRect[11][1] = { 7,6,10,9 };

	m_BlockRect[12][0] = { 10,6,12,8 };
	m_BlockRect[12][1] = { 10,6,12,8 };

	m_BlockRect[13][0] = { 12,6,14,10 };
	m_BlockRect[13][1] = { 12,6,14,10 };

	m_BlockRect[14][0] = { 0,10,2,12 };
	m_BlockRect[14][1] = { 0,10,2,12 };

	m_BlockRect[15][0] = { 2,8,5,12 };
	m_BlockRect[15][1] = { 2,8,5,12 };

	m_BlockRect[16][0] = { 5,9,9,12 };
	m_BlockRect[16][1] = { 5,9,9,12 };

	m_BlockRect[17][0] = { 9,8,12,12 };
	m_BlockRect[17][1] = { 9,8,12,12 };

	m_BlockRect[18][0] = { 12,10,14,12 };
	m_BlockRect[18][1] = { 12,10,14,12 };

	m_iBlockCntAnswer[0] = { 46 };
	m_iBlockCntAnswer[1] = { 32 };
	m_iBlockCntAnswer[2] = { 46 };
	m_iBlockCntAnswer[3] = { 40 };
	m_iBlockCntAnswer[4] = { 40 };
	m_iBlockCntAnswer[5] = { 26 };
	m_iBlockCntAnswer[6] = { 36 };
	m_iBlockCntAnswer[7] = { 26 };
	m_iBlockCntAnswer[8] = { 28 };
	m_iBlockCntAnswer[9] = { 20 };
	m_iBlockCntAnswer[10] = { 30 };
	m_iBlockCntAnswer[11] = { 30 };
	m_iBlockCntAnswer[12] = { 20 };
	m_iBlockCntAnswer[13] = { 28 };
	m_iBlockCntAnswer[14] = { 20 };
	m_iBlockCntAnswer[15] = { 34 };
	m_iBlockCntAnswer[16] = { 36 };
	m_iBlockCntAnswer[17] = { 34 };
	m_iBlockCntAnswer[18] = { 20 };

	m_TileBlockVec[0] = { 16,17,18,19,31,32,46,47 };
	m_TileBlockVec[1] = { 21,22,23 };
	m_TileBlockVec[2] = { 25,26,27,28,42,43,57,58 };
	m_TileBlockVec[3] = { 49,50,51,64,79 };
	m_TileBlockVec[4] = { 53,54,55,70,85 };
	m_TileBlockVec[5] = { 76,77 };
	m_TileBlockVec[6] = { 81,82,83,97 };
	m_TileBlockVec[7] = { 87,88 };
	m_TileBlockVec[8] = { 106,121,136 };
	m_TileBlockVec[9] = { 108 };
	m_TileBlockVec[10] = { 110,125,126 };
	m_TileBlockVec[11] = { 114,128,129 };
	m_TileBlockVec[12] = { 116 };
	m_TileBlockVec[13] = { 118,133,148 };
	m_TileBlockVec[14] = { 166 };
	m_TileBlockVec[15] = { 138,153, 154, 168, 169 };
	m_TileBlockVec[16] = { 156,157,158, 171,172,173 };
	m_TileBlockVec[17] = { 146,160,161,175,176 };
	m_TileBlockVec[18] = { 178 };
}

CStage4::~CStage4()
{
	Release();
}

void CStage4::Initialize()
{
#ifdef _DEBUG


#endif // _DEBUG
	int iPlayer_StartX = 9;
	int iPlayer_StartY = 9;

	m_pPlayer = CAbstractFactory<CPlayer>::Create((iPlayer_StartX * 40) + 40, (iPlayer_StartY * 40) + 60, L"player_start");
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, m_pPlayer);


	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((0 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((5 * 40) + 40, (4 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((3 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((8 * 40) + 40, (6 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((11 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));

	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));

	CObjMgr::GetInstance()->LoadStage4();

	m_hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage2");
	m_pTileVector = CObjMgr::GetInstance()->GetTilePtr();
	m_pMarkList = CObjMgr::GetInstance()->GetListPtr(OBJ_MARK);

	for (auto& pTile : *m_pTileVector)
	{
		pTile->Render(m_hBackGround);
		int iStart = pTile->GetFrame().iStart;
		if (iStart >= 11 && iStart <= 17)
		{
			float fX = pTile->GetInfo()->fX;
			float fY = pTile->GetInfo()->fY;
			
			switch (iStart)
			{
			case 11:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX + fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 12:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX - fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 13:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY - fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX + fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 14:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY - fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX - fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX + fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 15:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY - fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX - fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 16:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY - fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX, fY + fMarkDeltaY, L"Mark"));
				break;
			case 17:
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX - fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX , fY + fMarkDeltaY, L"Mark"));
				CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(fX + fMarkDeltaX, fY + fMarkDeltaY, L"Mark"));
				break;
			default:
				break;
			}
			pTile->SetDraw(false);
		}
	}
	CSoundMgr::Get_Instance()->PlaySound(L"StageStart_7.wav", STAGE_START, 0.2f);
}

int CStage4::Update()
{
	if (m_iClearRangeCnt>=19)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_WIN;
		dynamic_cast<CPlayer*>(m_pPlayer)->SetWin();
		ChangeScene();
	}
	else if (CObjMgr::GetInstance()->GetRemainPlayer() == false)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		m_eCurSceneState = SCENE_LOSE;
		ChangeScene();
	}
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage4::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
	//범위 완성 확인
	for (int i = 0; i < 19 ; i++)
	{
		if (m_bBlockCheck[i] == false) 
		{
			m_iBlockCnt[i] = 0; 
			for (auto pMark : *(m_pMarkList))
			{
				if (CheckRange(m_BlockRect[i][0], pMark) || CheckRange(m_BlockRect[i][1], pMark)) 
					++m_iBlockCnt[i]; 
			}
			if (m_iBlockCnt[i] == m_iBlockCntAnswer[i]) 
			{
				m_bBlockCheck[i] = true;
				++m_iClearRangeCnt;
				for (auto TileIndex : m_TileBlockVec[i])
					(*m_pTileVector)[TileIndex]->SetStartFrame(19);
			}
		}
	}
	// 완성된 범위 Mark 지우기
	for (int i = 0; i < 19; i++)
	{
		if (m_bBlockCheck[i] == true)
		{
			for (auto pMark : *(m_pMarkList))
			{
				if (CheckRange(m_BlockRect[i][0], pMark) || CheckRange(m_BlockRect[i][1], pMark))
					pMark->SetDraw(false);
			}
		}
	}
	// 미완성 범위 Mark 그리기
	for (int i = 0; i < 19; i++)
	{
		if (m_bBlockCheck[i] == false)
		{
			for (auto pMark : *(m_pMarkList))
			{
				if (CheckRange(m_BlockRect[i][0], pMark) || CheckRange(m_BlockRect[i][1], pMark))
					pMark->SetDraw(true);
			}
		}
	}

	if (m_eCurSceneState == SCENE_START || m_eCurSceneState == SCENE_WIN)
	{
		if (m_eCurSceneState == SCENE_START && m_fAlpha > 0.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha -= 0.015f;
		}
		else if (m_eCurSceneState == SCENE_WIN && m_fAlpha < 1.f && m_dwFrameTime + 10 <= GetTickCount64())
		{
			m_dwFrameTime = GetTickCount64();
			m_fAlpha += 0.008f;
		}
		CheckSceneFrame();
	}
}

void CStage4::Render(HDC hDC)
{	
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		m_hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC); 
	//HDC hTemp = CBmpMgr::GetInstance()->FindImage(L"dart_obj");
	//
	//BitBlt(hDC,							// 목적지 DC
	//	0, 0,
	//	27, 9,
	//	hTemp,					// 원본 DC
	//	0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
	//	0,
	//	SRCCOPY);						// 그대로 복사하여 출력

	int iItemCnt = 0;
	for (auto& pitem : *(CInven::GetInstance()->GetItemSlotPtr()))
	{
		switch (pitem->GetFrame().iStart)
		{
		case 0:
			++iItemCnt;
			continue;
		case 1:
			if (CInven::GetInstance()->GetInven().iNeedleCnt <= 0)
			{
				++iItemCnt;
				continue;
			}
			break;
		case 2:
			if (CInven::GetInstance()->GetInven().iDartCnt <= 0)
			{
				++iItemCnt;
				continue;
			}
			break;
		case 3:
			if (CInven::GetInstance()->GetInven().iShieldCnt <= 0)
			{
				++iItemCnt;
				continue;
			}
			break;
		default:
			break;
		}
		HDC hSlotNum = CBmpMgr::GetInstance()->FindImage(L"InGameNumber");

		BitBlt(hDC,							// 목적지 DC
			243 + 40 * iItemCnt,
			568,
			13, 11,
			hSlotNum,						// 원본 DC
			13 * iItemCnt,					// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
			0,
			SRCCOPY);						// 그대로 복사하여 출력

		HDC hSlotItem = CBmpMgr::GetInstance()->FindImage(L"InGameSlot");
		GdiTransparentBlt(hDC,						// 목적지 DC
			243 + 40 * iItemCnt,					// 목적지 LEFT, TOP
			568,
			37,										// 목적지 공간의 가로, 세로 사이즈
			29,
			hSlotItem,								// 원본 이미지 DC
			37 * (pitem->GetFrame().iStart - 1),	// 원본 이미지 LEFT, TOP
			0,
			37,										// 원본 이미지 가로, 세로 사이즈
			29,
			RGB(255, 0, 255));						// 제거할 픽셀 색상
		++iItemCnt;
	}
	if (m_eCurSceneState == SCENE_START)
	{
		Graphics* _pGraphics = Graphics::FromHDC(hDC);
		Gdiplus::Image* pBlackImg = CImgMgr::GetInstance()->FindImg(L"black_bg");

		Rect rect = { 0,0,800,600 };

		ImageAttributes attr;
		MakeAlphaAttr(attr, m_fAlpha);
		_pGraphics->DrawImage(pBlackImg, rect, 0, 0, WINCX, WINCY, UnitPixel, &attr);
	}
}

void CStage4::Release()
{
	CObjMgr::GetInstance()->ReleaseRenderList();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_PLAYER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BOMB);
	CObjMgr::GetInstance()->DeleteObj(OBJ_WAVE);
	CObjMgr::GetInstance()->DeleteObj(OBJ_BUTTON);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MONSTER);
	CObjMgr::GetInstance()->DeleteObj(OBJ_ITEM);
	CObjMgr::GetInstance()->DeleteObj(OBJ_MARK);
	CObjMgr::GetInstance()->DeleteTile();
}

bool CStage4::CheckRange(INTRECT tIntRect, CObj* pMark)
{
	float fX = pMark->GetInfo()->fX;
	float fY = pMark->GetInfo()->fY;

	int iLIndex = tIntRect.iLeft;
	int iTIndex = tIntRect.iTop;
	int iRIndex = tIntRect.iRight;
	int iBIndex = tIntRect.iBottom;

	if (iLIndex * 40 + 40 <= fX && fX <= iRIndex * 40 + 40
		&& 
		iTIndex * 40 + 60 + fMarkDeltaY <= fY && fY <= iBIndex * 40 + 60 + fMarkDeltaY
		&&
		pMark->GetFrame().iStart == 1)
	{
		return true;
	}
	return false;
}
void CStage4::CheckSceneFrame()
{
	if (m_eCurSceneState == SCENE_START && m_fAlpha < 0.f)
	{
		m_eCurSceneState = SCENE_PLAY;
		CSoundMgr::Get_Instance()->PlayBGM(L"StageBGM.wav", 0.1f);
	}
	else if (m_eCurSceneState == SCENE_END && m_fAlpha >= 1.f)
	{

	}
}

void CStage4::ChangeScene()
{
	if (m_ePreSceneState == m_eCurSceneState)
		return;
	switch (m_eCurSceneState)
	{
	case SCENE_START:
		m_dwFrameTime = GetTickCount64();
		break;
	case SCENE_WIN:
		CSoundMgr::Get_Instance()->PlaySound(L"Win.wav", SOUND_EFFECT, 0.2f);
		CObjMgr::GetInstance()->DestroyMonster();
		break;
	case SCENE_LOSE:
		break;
	default:
		break;
	}
	m_ePreSceneState = m_eCurSceneState;
}

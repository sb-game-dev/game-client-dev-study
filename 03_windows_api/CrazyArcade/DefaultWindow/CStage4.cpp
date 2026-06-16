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
CStage4::CStage4()
{
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
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create((iPlayer_StartX * 40) + 40, (iPlayer_StartY * 40) + 60, L"player_start"));

	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((0 * 40) + 40, (0 * 40) + 60, L"Bean_Monster_Start"));

	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((5 * 40) + 40, (4 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((3 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((8 * 40) + 40, (6 * 40) + 60, L"Bean_Monster_Start"));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CAbstractFactory<CMonster>::Create((11 * 40) + 40, (12 * 40) + 60, L"Bean_Monster_Start"));


	CObjMgr::GetInstance()->AddObject(OBJ_BUTTON, CAbstractFactory<CButton>::Create(717, 576, L"button_stageExit"));


	//CObjMgr::GetInstance()->AddObject(OBJ_MARK, CAbstractFactory<CMark>::Create(40, 60, L"Mark"));

	CObjMgr::GetInstance()->LoadStage4();

	m_hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage2");
	vector<CObj*> TileVector = CObjMgr::GetInstance()->GetTile();

	for (auto& pTile : TileVector)
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
	CObjMgr::GetInstance()->Update();
	return 0;
}

void CStage4::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage4::Render(HDC hDC)
{
	//HDC hBackGround = CBmpMgr::GetInstance()->FindImage(L"stage_background"); //stage2
	
	BitBlt(hDC,							// 목적지 DC
		0, 0,
		WINCX, WINCY,
		m_hBackGround,					// 원본 DC
		0,								// 원본 이미지에서 가져오기 시작할 좌표의 LEFT, TOP
		0,
		SRCCOPY);						// 그대로 복사하여 출력

	CObjMgr::GetInstance()->Render(hDC);
}

void CStage4::Release()
{
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

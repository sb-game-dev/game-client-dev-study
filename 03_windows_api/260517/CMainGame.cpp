#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
CMainGame::CMainGame():m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}


void CMainGame::Initialize()
{
	m_hDC = GetDC(g_Hwnd);
	
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->SetBullet(&m_ObjList[OBJ_BULLET]);

	for (int i = 0; i < 5; i++)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(float(rand()%WINCX) , float(rand() % WINCY),100,10));
}

void CMainGame::Update()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	
	for (auto i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			bool iResult = (*iter)->Update();
			if(iResult)
			{
				Safe_Delete((*iter));
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}
void CMainGame::LateUpdate()
{
	for (auto i = 0; i < OBJ_END; i++)
	{
		for (auto& Obj : m_ObjList[i])
		{
			Obj->LateUpdate();
		}
	}
	CollisionCheck(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CMainGame::CollisionCheck(list<CObj*> listDst, list<CObj*> listSrc)
{
	if (!listDst.size() || !listSrc.size())
		return;
	// 1. IntersectRect 사용
	//RECT rResult;
	//
	//for (auto ObjDst : listDst)
	//{
	//	for (auto ObjSrc : listSrc)
	//	{
	//		if (IntersectRect(&rResult, (ObjDst->GetRect()), (ObjSrc->GetRect())))
	//		{
	//			ObjDst->TakeDamage(ObjSrc->GetStat().fAttack);
	//			ObjSrc->TakeDamage(ObjDst->GetStat().fAttack);
	//		}
	//	}
	//}
	// 2. 피타고라스 정리 사용
	for (auto ObjDst : listDst)
	{
		for (auto ObjSrc : listSrc)
		{
			double fDistance = sqrt((ObjDst->GetInfo().fX - ObjSrc->GetInfo().fX) * (ObjDst->GetInfo().fX - ObjSrc->GetInfo().fX) 
				+ (ObjDst->GetInfo().fY - ObjSrc->GetInfo().fY) * (ObjDst->GetInfo().fY - ObjSrc->GetInfo().fY));
			double fSize = sqrt((ObjDst->GetInfo().fCX - ObjSrc->GetInfo().fCX) * (ObjDst->GetInfo().fCX - ObjSrc->GetInfo().fCX)
				+ (ObjDst->GetInfo().fCY - ObjSrc->GetInfo().fCY) * (ObjDst->GetInfo().fCY - ObjSrc->GetInfo().fCY));
			if (fDistance <= fSize)
			{
				ObjDst->TakeDamage(ObjSrc->GetStat().fAttack);
				ObjSrc->TakeDamage(ObjDst->GetStat().fAttack);
			}
		}
	}
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);

		m_dwTime = GetTickCount();

		m_iFPS = 0;

		SetWindowText(g_Hwnd, m_szFPS);
	}

	for (auto i = 0; i < OBJ_END; i++)
	{
		for (auto& Obj : m_ObjList[i])
			Obj->Render(m_hDC);
	}

	TCHAR szBuff[32] = L"";
	swprintf_s(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());//
	TextOut(m_hDC, 30, 30, szBuff, lstrlen(szBuff));
	
}

void CMainGame::Release()
{
	for (auto i = 0; i < OBJ_END; i++)
	{
		for (auto& Obj : m_ObjList[i])
		{
			Safe_Delete(Obj);
		}
		m_ObjList[i].clear();
	}
}


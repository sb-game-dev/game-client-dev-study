#include "pch.h"
#include "CInven.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CButton.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CItem.h"
#include "CMouse.h"

CInven* CInven::m_pInstance = nullptr;
CInven::CInven():m_iGold(100000),m_bDraw(false), m_bButtonCurState(false), m_bButtonPreState(false), m_iPreSlotIndex(- 1)
{
	m_pMouse = CObjMgr::GetInstance()->GetList(OBJ_MOUSE).front();

	m_ItemStorage.reserve(8);
	m_ItemSlot.reserve(6);

	m_pExitButton =  CAbstractFactory<CButton>::Create(303.5, 520.5, L"button_InvenExit");
	m_ItemSlot.push_back(CAbstractFactory<CButton>::Create(569 + 11.5, 175 + 10.5, L"Slot1"));
	m_ItemSlot.push_back(CAbstractFactory<CButton>::Create(489 + 11.5, 235 + 10.5, L"Slot2"));
	m_ItemSlot.push_back(CAbstractFactory<CButton>::Create(569 + 11.5, 295 + 10.5, L"Slot3"));
	m_ItemSlot.push_back(CAbstractFactory<CButton>::Create(649 + 11.5, 235 + 10.5, L"Slot4"));

	ZeroMemory(&m_tItemStorageCnt, sizeof(m_tItemStorageCnt));
}
CInven::~CInven()
{
	Release();
}
void CInven::Initialize()
{
}
int CInven::Update()
{
	return 0;
}
void CInven::LateUpdate()
{
	if (m_bDraw == false)
		return;

	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ExitButtonUpdate();
	for (int i = 0;i<m_ItemSlot.size();i++)
	{
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON) && PtInRect(m_ItemSlot[i]->GetRect(), ptMouse))
		{
			if (dynamic_cast<CMouse*>(m_pMouse)->GetChoiceItem() == -1)
			{
				dynamic_cast<CMouse*>(m_pMouse)->SetChoiceItem(m_ItemSlot[i]->GetFrame().iStart - 1);
				m_ItemSlot[i]->SetStartFrame(0);
				m_iPreSlotIndex = i;
			}
		}
		if (CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON) 
			&& PtInRect(m_ItemSlot[i]->GetRect(), ptMouse))
		{
			if (dynamic_cast<CMouse*> (m_pMouse)->GetChoiceItem() >= 0) // 마우스에 옮길 아이템이 들려있을 때
			{
				if (m_ItemSlot[i]->GetFrame().iStart > 0) // 슬롯에 이미 장착한 아이템이 있을 때
				{
					int iTempItem = m_ItemSlot[i]->GetFrame().iStart;
					m_ItemSlot[i]->SetStartFrame(dynamic_cast<CMouse*> (m_pMouse)->GetChoiceItem() + 1); //목적지 슬롯 아이템 변경
					if (m_iPreSlotIndex != -1) // 출발지가 스토리지가 아니라 슬롯이라면
					{
						m_ItemSlot[m_iPreSlotIndex]->SetStartFrame(iTempItem);
						m_iPreSlotIndex = -1;
					}
				}
				else
				{
					m_ItemSlot[i]->SetStartFrame(dynamic_cast<CMouse*> (m_pMouse)->GetChoiceItem()+1);
				}
			}
			dynamic_cast<CMouse*> (m_pMouse)->SetChoiceItem(-1);
		}
	}
	
	//for (auto& pStorage : m_ItemStorage)
	for (int i = 0; i < m_ItemStorage.size(); i++)
	{
		if (CKeyMgr::GetInstance()->KeyPressing(VK_LBUTTON))
		{
			RECT rc = { m_ItemStorage[i]->GetInfo()->fX - m_ItemStorage[i]->GetInfo()->fCX,
						m_ItemStorage[i]->GetInfo()->fY - m_ItemStorage[i]->GetInfo()->fCY,
						m_ItemStorage[i]->GetInfo()->fX + m_ItemStorage[i]->GetInfo()->fCX,
						m_ItemStorage[i]->GetInfo()->fY + m_ItemStorage[i]->GetInfo()->fCY,
			};
			if (PtInRect(&rc, ptMouse))
			{
				if (dynamic_cast<CMouse*> (m_pMouse)->GetChoiceItem() == -1)
				{
					dynamic_cast<CMouse*> (m_pMouse)->SetChoiceItem(m_ItemStorage[i]->GetFrame().iStart);
					//Safe_Delete(m_ItemStorage[i]);
					//m_ItemStorage.erase(m_ItemStorage.begin() + i);
					////UpdateStoragePos();
					//cout << "마우스로 듦" << endl;
					//cout << m_ItemStorage.size() << endl;
				}
			}
		}
		else
		{
			dynamic_cast<CMouse*> (m_pMouse)->SetChoiceItem(-1);
		}
	}
	//if (CKeyMgr::GetInstance()->KeyUp(VK_LBUTTON))
	//{
	//	if (ptMouse.y < 411)
	//	{
	//		if (dynamic_cast<CMouse*>(m_pMouse)->GetChoiceItem() != -1)
	//		{
	//			int iX = m_ItemStorage.size();
	//			switch (dynamic_cast<CMouse*>(m_pMouse)->GetChoiceItem())
	//			{
	//			case 1:
	//				m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE1));
	//				break;
	//			case 2:
	//				m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE2));
	//				break;
	//			case 3:
	//				m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", PUSH));
	//				break;
	//			default:
	//				break;
	//			}
	//			cout << "스토리치에 추가 후 스토리지 사이즈: " << m_ItemStorage.size() << endl;
	//		}
	//	}
	//}
}
void CInven::Render(HDC hDC)
{
	if (m_bDraw == false)
		return;
	HDC hMyPage = CBmpMgr::GetInstance()->FindImage(L"MyPage");
	GdiTransparentBlt(hDC,185,16,595,538,hMyPage,0,0,595,538,RGB(255, 0, 255));	

	HDC hExitButton = CBmpMgr::GetInstance()->FindImage(L"button_InvenExit");
	BitBlt(hDC, 238, 505, 137, 31, hExitButton, 137 * m_pExitButton->GetFrame().iStart, 0, SRCCOPY);

	HDC hSlot1 = CBmpMgr::GetInstance()->FindImage(L"Slot1");
	switch (m_ItemSlot[0]->GetFrame().iStart)
	{
	case 1:
		if(m_tItemStorageCnt.iNeedleCnt>0)
			BitBlt(hDC, 569, 175, 33, 31, hSlot1, 33 * m_ItemSlot[0]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 2:
		if (m_tItemStorageCnt.iDartCnt > 0)
			BitBlt(hDC, 569, 175, 33, 31, hSlot1, 33 * m_ItemSlot[0]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 3:
		if (m_tItemStorageCnt.iShieldCnt > 0)
			BitBlt(hDC, 569, 175, 33, 31, hSlot1, 33 * m_ItemSlot[0]->GetFrame().iStart, 0, SRCCOPY);
		break;
	default:
		break;
	}
	HDC hSlot2 = CBmpMgr::GetInstance()->FindImage(L"Slot2");
	switch (m_ItemSlot[1]->GetFrame().iStart)
	{
	case 1:
		if (m_tItemStorageCnt.iNeedleCnt > 0)
			BitBlt(hDC, 489, 235, 33, 31, hSlot2, 33 * m_ItemSlot[1]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 2:
		if (m_tItemStorageCnt.iDartCnt > 0)
			BitBlt(hDC, 489, 235, 33, 31, hSlot2, 33 * m_ItemSlot[1]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 3:
		if (m_tItemStorageCnt.iShieldCnt > 0)
			BitBlt(hDC, 489, 235, 33, 31, hSlot2, 33 * m_ItemSlot[1]->GetFrame().iStart, 0, SRCCOPY);
		break;
	default:
		break;
	}
	
	HDC hSlot3 = CBmpMgr::GetInstance()->FindImage(L"Slot3");
	switch (m_ItemSlot[2]->GetFrame().iStart)
	{
	case 1:
		if (m_tItemStorageCnt.iNeedleCnt > 0)
			BitBlt(hDC, 569, 295, 33, 31, hSlot3, 33 * m_ItemSlot[2]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 2:
		if (m_tItemStorageCnt.iDartCnt > 0)
			BitBlt(hDC, 569, 295, 33, 31, hSlot3, 33 * m_ItemSlot[2]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 3:
		if (m_tItemStorageCnt.iShieldCnt > 0)
			BitBlt(hDC, 569, 295, 33, 31, hSlot3, 33 * m_ItemSlot[2]->GetFrame().iStart, 0, SRCCOPY);
		break;
	default:
		break;
	}
	
	
	HDC hSlot4 = CBmpMgr::GetInstance()->FindImage(L"Slot4");
	switch (m_ItemSlot[3]->GetFrame().iStart)
	{
	case 1:
		if (m_tItemStorageCnt.iNeedleCnt > 0)
			BitBlt(hDC, 649, 235, 33, 31, hSlot4, 33 * m_ItemSlot[3]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 2:
		if (m_tItemStorageCnt.iDartCnt > 0)
			BitBlt(hDC, 649, 235, 33, 31, hSlot4, 33 * m_ItemSlot[3]->GetFrame().iStart, 0, SRCCOPY);
		break;
	case 3:
		if (m_tItemStorageCnt.iShieldCnt > 0)
			BitBlt(hDC, 649, 235, 33, 31, hSlot4, 33 * m_ItemSlot[3]->GetFrame().iStart, 0, SRCCOPY);
		break;
	default:
		break;
	}
	
	for (auto& pStorage : m_ItemStorage)
	{
		HDC hStorage = CBmpMgr::GetInstance()->FindImage(pStorage->GetFrameKey());
		BitBlt(hDC, 
			pStorage->GetInfo()->fX-30, 
			pStorage->GetInfo()->fY-25,
			60, 50, 
			hStorage,
			60 * pStorage->GetFrame().iStart, 0,
			SRCCOPY);

		Rectangle(hDC,
			(int)(pStorage->GetRect()->left),
			(int)(pStorage->GetRect()->top),
			(int)(pStorage->GetRect()->right),
			(int)(pStorage->GetRect()->bottom)
		);
		TCHAR	szBuff[32] = L"";
		int iCnt = 0;
		switch (pStorage->GetFrame().iStart)
		{
		case 0:
			iCnt = m_tItemStorageCnt.iNeedleCnt;
			break;
		case 1:
			iCnt = m_tItemStorageCnt.iDartCnt;
			break;
		case 2:
			iCnt = m_tItemStorageCnt.iShieldCnt;
			break;
		default:
			break;
		}
		swprintf_s(szBuff, L"%d", iCnt); 
		SetBkMode(hDC, TRANSPARENT); 
		SetTextColor(hDC, RGB(255, 255, 255));
		if(iCnt>10)
			TextOut(hDC, pStorage->GetInfo()->fX + 11, pStorage->GetInfo()->fY + 10, szBuff, lstrlen(szBuff));
		else
			TextOut(hDC, pStorage->GetInfo()->fX + 19, pStorage->GetInfo()->fY + 10, szBuff, lstrlen(szBuff));
	}
}
void CInven::Release()
{
	Safe_Delete(m_pExitButton);

	for (auto& pItem : m_ItemSlot)
	{
		Safe_Delete(pItem);
	}

	for (auto& pItem : m_ItemStorage)
	{
		Safe_Delete(pItem);
	}
}

void CInven::AddItemToStorage(ITEMTYPE eID)
{
	int iStorageNum = m_ItemStorage.size();
	int iX = iStorageNum % 4;
	int iY = iStorageNum / 4;
	switch (eID)
	{
	case IT_NEEDLE:
		if (m_tItemStorageCnt.iNeedleCnt == 0)
			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE1));
		m_tItemStorageCnt.iNeedleCnt += 5;
		break;
	case IT_DART:
		if (m_tItemStorageCnt.iDartCnt == 0)
			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE2));
		m_tItemStorageCnt.iDartCnt+= 3;
		break;
	case IT_SHIELD:
		if (m_tItemStorageCnt.iShieldCnt == 0)
			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", PUSH));
		m_tItemStorageCnt.iShieldCnt += 1;
		break;
	//case IT_TRAMPOLINE:
	//	m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 175 + 10.5, L"InvenItem", BREAK));
	//	break;
	default:
		break;
	}
}

void CInven::ExitButtonUpdate()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_bButtonPreState = m_bButtonCurState;
	if (PtInRect(m_pExitButton->GetRect(), ptMouse))
	{
		m_bButtonCurState = true;
		m_pExitButton->SetStartFrame(1);
		if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON))
		{
			m_bDraw = false;
			CSoundMgr::Get_Instance()->PlaySound(L"buttonClick_2.wav", BUTTON_CLICK, 0.3f);
		}
	}
	else
	{
		m_bButtonCurState = false;
		m_pExitButton->SetStartFrame(0);
	}
	if (m_bButtonCurState && !m_bButtonPreState)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"buttonCursor_0.wav", BUTTON_CURSOR, 0.1f);
	}
}

void CInven::UpdateStoragePos()
{
	cout << "UpdateStoragePos" << endl;
	//for (int i = 0; i < m_ItemStorage.size(); ++i)
	//{
	//	int iX = i % 4;
	//	int iY = i / 4;
	//	switch (m_ItemStorage[i]->GetFrame().iStart)
	//	{
	//	case IT_NEEDLE:
	//		//if (m_tItemStorageCnt.iNeedleCnt > 0)
	//			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE1));
	//		break;
	//	case IT_DART:
	//		//if (m_tItemStorageCnt.iDartCnt > 0)
	//			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", TILE2));
	//		break;
	//	case IT_SHIELD:
	//		//if (m_tItemStorageCnt.iShieldCnt > 0)
	//			m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 411, L"InvenItem", PUSH));
	//		break;
	//		//case IT_TRAMPOLINE:
	//		//	m_ItemStorage.push_back(CAbstractFactory<CButton>::Create(478 + iX * 72, 175 + 10.5, L"InvenItem", BREAK));
	//		//	break;
	//	default:
	//		break;
	//	}
	//}
}

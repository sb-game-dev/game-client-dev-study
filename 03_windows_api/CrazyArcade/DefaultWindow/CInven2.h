#pragma once
#include "Define.h"
#include "CObj.h"

class CInven2
{
public:
	CInven2();
	CInven2(const CInven2* rhs) = delete;
	CInven2& operator=(const CInven2* rhs) = delete;
	~CInven2();

public:
	void	Initialize();
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

public:
	void			SetGold(int iGold) { m_iGold += iGold; }
	void			SetDraw(bool bDraw) { m_bDraw = bDraw; }
	void			SetNeedleCnt(int iNeedle) { m_tItemStorageCnt.iNeedleCnt += iNeedle; }
	void			SetDartCnt(int iDart) { m_tItemStorageCnt.iDartCnt += iDart; }
	void			SetShieldCnt(int iShield) { m_tItemStorageCnt.iShieldCnt += iShield; }

	int				GetGold() { return m_iGold; }
	bool			GetDraw() { return m_bDraw; }
	bool* GetDrawPtr() { return &m_bDraw; }
	INVEN			GetInven() { return m_tItemStorageCnt; }
	vector<CObj*>* GetItemSlotPtr() { return &m_ItemSlot; }
	vector<CObj*>	GetItemSlot() { return m_ItemSlot; }

	void			AddItemToStorage(ITEMTYPE eID);

private:
	void			ExitButtonUpdate();
	void			UpdateStoragePos();

public:
	static CInven2* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CInven2;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CInven2* m_pInstance;

	int				m_iGold;

	vector<CObj*>	m_ItemSlot;
	vector<CObj*>	m_ItemStorage;

	bool			m_bDraw;

	CObj* m_pExitButton;


	bool			m_bButtonCurState;
	bool			m_bButtonPreState;

	INVEN			m_tItemStorageCnt;

	CObj* m_pMouse;
	int				m_iPreSlotIndex;


};


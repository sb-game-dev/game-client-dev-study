#pragma once
#include "CObj.h"
#include "Define.h"
class CItem :public CObj
{
public :
	CItem(const char* szName,int iHp,int iAttack,int iMoney);
	CItem(const CObj& rhs);
	~CItem();

public:
	void Render() override;
	ITEMTYPE GetItemType() { return m_ItemType; }
	ITEMSTATE GetItemState() { return m_ItemState; }

	void SetItemState(ITEMSTATE IS) { m_ItemState = IS; }
private:
	ITEMTYPE m_ItemType;
	ITEMSTATE m_ItemState;
};


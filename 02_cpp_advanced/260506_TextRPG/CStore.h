#pragma once
class CObj;
class CStore
{
private:
	enum ItemType { WEAPON, ARMOR, END_IT };
	enum ItemClass { NORMAL, MAGIC, RARE, END_IC };
	enum StoreMenu { BUY = 1, SELL, END_STOREMENU };
public:
	CStore();
	~CStore();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	void Initialize();
	void Update();
	void Release();

private:
	void Buy();
	void Sell();

	void Render(ItemClass IC);
private:
	CObj* m_pPlayer;
	CObj* m_pItem[END_IT][END_IC];
};


#pragma once
class CPlayer;

class CShop
{
private:
	CShop();
	~CShop();

public:
	void Update();
	void SetPlayer(CPlayer* pPlayer) { m_pCopyPlayer = pPlayer; }
	static CShop* Create();
	void Destroy();

private:
	CPlayer* m_pCopyPlayer;

private:
	void Weapon();
	void Armor();
};


#pragma once
class CPlayer;

class CShop
{
private:
	CShop();
	~CShop();

public:
	void Initialize();
	void Update();
	void Release();

	static CShop* Create();
	void Destroy();

	void SetPlayer(CPlayer* pObj) { m_pCopyPlayer = pObj; }

private:
	CPlayer* m_pCopyPlayer;

	void Weapon();
	void Armor();
};


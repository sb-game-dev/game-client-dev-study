#pragma once
#include <vector>
using namespace std;
class CObj;
class CInven
{
public :
	CInven();
	~CInven();

public:
	void Update();
	void Release();

	void Render();

	bool AddItem(CObj* pItem);
	int DeleteItem(int iNum);

	void EquipItem();
	void UnEquipItem();
public :
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
private:
	CObj* m_pPlayer;
	vector<CObj*> m_vecInvenP;
	const int iSize;
};


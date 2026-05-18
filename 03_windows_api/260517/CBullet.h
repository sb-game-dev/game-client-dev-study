#pragma once
#include "CObj.h"
class CBullet:public CObj
{
public :
	CBullet();
	~CBullet();

public:
	void Initialize()			override;
	bool Update()				override;
	void Render(HDC hDC)		override;
	void Release()				override;

public:

	// CObj을(를) 통해 상속됨
	void LateUpdate() override;
	BULLETSTATE GetState() { return m_State; }
	void SetState(BULLETSTATE eState) { m_State = eState; }
	void SetBullet(list<CObj*>* pBulletList) { m_BulletListP = pBulletList; }
private:
	DWORD dwTime;

	list<CObj*>* m_BulletListP;
	BULLETSTATE m_State;
};


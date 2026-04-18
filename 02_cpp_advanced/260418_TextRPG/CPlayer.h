#pragma once
#include"CObj.h"
class CPlayer:public CObj
{
private:
	CPlayer();
	~CPlayer();
	enum JOBINDEX { WARRIOR = 1, MAGE, THIEF };
public:
	void Initialize();
	void Update();
	void Release();

	static CPlayer* Create();
	void Destroy();


};


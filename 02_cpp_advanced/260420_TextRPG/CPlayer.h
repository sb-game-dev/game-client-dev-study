#pragma once
#include "CObj.h"

class CPlayer:public CObj
{
private:
	CPlayer();
	~CPlayer();
	enum JobIndex {WARRIOR=1,MAGE,THIEF};
public:
	void Initialize();
	static CPlayer* Create();
	void Destroy();

};


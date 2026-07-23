#pragma once
#include "CBase.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
public:
	explicit CKeyMgr();
	virtual  ~CKeyMgr();

public :
	bool	KeyPressing(int iKey);
	bool	KeyUp(int iKey);
	bool	KeyDown(int iKey);
	void	KeyUpdate();
private:

	bool m_bCurState[0xff];
	bool m_bPreState[0xff];
};

END
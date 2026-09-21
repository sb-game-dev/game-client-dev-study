#pragma once

#include "Engine_Defines.h"

#include "Client_Defines.h"

/* CMainApp : 객체지향적인 게임의 구현을 위해 CMainApp의 Update, Render함수의 반복적인 호출을 한다. */
NS_BEGIN(Client)

class CMainApp final
{
private:
	CMainApp();
public:
	~CMainApp() = default;


public:
	HRESULT Initialize();
	void Update();
	HRESULT Render();

public:
	static unique_ptr<CMainApp> Create();

};

NS_END

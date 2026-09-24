#pragma once

#include "Engine_Defines.h"
#include "Client_Defines.h"

#include "Timer.h"

/* CMainApp : 객체지향적인 게임의 구현을 위해 CMainApp의 Update, Render함수의 반복적인 호출을 한다. */
NS_BEGIN(Client)

class CMainApp final
{
private:
	CMainApp();
public:
	~CMainApp();


public:
	HRESULT Initialize();
	void Update(f32_t fTimeDelta);
	HRESULT Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

public:
	static unique_ptr<CMainApp> Create();

};

NS_END

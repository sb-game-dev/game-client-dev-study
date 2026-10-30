#pragma once

#include "Client_Defines.h"
#include "Level.h"

NS_BEGIN(Client)

class CLevel_GamePlay final : public CLevel
{
private:
	CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CLevel_GamePlay() = default;

public:
	HRESULT Initialize();
	void Update(f32_t fTimeDelta);
	HRESULT Render();

private:
	HRESULT Ready_Layer_Camera(const tchar_t* pLayerTag);
	HRESULT Ready_Layer_BackGround(const tchar_t* pLayerTag);


public:
	static shared_ptr<CLevel_GamePlay> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END
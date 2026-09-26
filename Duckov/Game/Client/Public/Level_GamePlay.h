#pragma once
#include "Client_Defines.h"
#include "Level.h"
#include "QuarterView_Cam.h"
NS_BEGIN(Client)
class CLevel_GamePlay final : public CLevel
{
private:
	CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_GamePlay() = default;

public:
	virtual		HRESULT		Initialize() override;
	virtual		void		Update(f32_t fDeltaTime) override;
	virtual		void		LateUpdate(f32_t fDeltaTime) override;
	virtual		HRESULT		Render() override;

private:
	shared_ptr<CQuarterView_Cam>		m_pCamera;

public:
	static shared_ptr<CLevel_GamePlay> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END

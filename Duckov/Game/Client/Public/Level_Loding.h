#pragma once
#include "Client_Defines.h"
#include "Level.h"

NS_BEGIN(Client)
class CLevel_Loding final : public CLevel
{
private:
	CLevel_Loding(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_Loding() = default;

public:
	virtual HRESULT	Initialize() override;
	virtual void	Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

public:
	static shared_ptr<CLevel_Loding> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END

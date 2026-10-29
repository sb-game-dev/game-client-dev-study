#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CLevel_MapTool final : public CLevel
{
private:
	CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_MapTool() = default;

public:
	virtual		HRESULT		Initialize() override;
	virtual		void		Update(f32_t fDeltaTime) override;
	virtual		HRESULT		Render() override;


private:
	HRESULT Ready_Layer_BackGround(const tchar_t* pLayerTag);
	HRESULT Ready_Layer_GameObject(const tchar_t* pLayerTag);
public:
	static shared_ptr<CLevel_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END

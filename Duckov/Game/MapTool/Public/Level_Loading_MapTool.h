#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CLevel_Loading_MapTool final : public CLevel
{
private:
	CLevel_Loading_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_Loading_MapTool() = default;

public:
	virtual HRESULT	Initialize(LEVEL eNextLevel);
	virtual void	Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

private:
	LEVEL								m_eNextLevelID = { LEVEL::END };
	shared_ptr<class CLoader_MapTool>	m_pLoader = { nullptr };

public:
	static shared_ptr<CLevel_Loading_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel);
};
NS_END
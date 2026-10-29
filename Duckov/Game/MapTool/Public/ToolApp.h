#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CImGui_Manager;
class CTool;
class CToolApp final
{
private:
	CToolApp() = default;
public:
	~CToolApp();

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	unique_ptr<CImGui_Manager>			m_pImGui_Manager = { nullptr };
	unique_ptr<CTool>					m_pTool = { nullptr };
public:
	static		unique_ptr<CToolApp>		Create();
};

NS_END

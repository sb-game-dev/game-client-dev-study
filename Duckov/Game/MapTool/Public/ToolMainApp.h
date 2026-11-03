#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)

class CToolMainApp final
{
private:
	CToolMainApp() = default;
public:
	~CToolMainApp();

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

private:
	HRESULT								Start_Level(LEVEL eStartLevelID);

public:
	static		unique_ptr<CToolMainApp>		Create();
};

NS_END

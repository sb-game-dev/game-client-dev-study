#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CTool;
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

	unique_ptr<CTool>					m_pTool = { nullptr };
	bool_t								m_bReadyImGui = { false };

private:
	HRESULT								Ready_ImGui();
	HRESULT								Begin_ImGui();
	HRESULT								Render_ImGui();
	HRESULT								Shutdown_ImGui();

	void								Sync_SceneView();

public:
	static		unique_ptr<CToolMainApp>		Create();
};

NS_END

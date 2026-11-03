#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CEditorUI;
class CLevel_MapTool final : public CLevel
{
private:
	CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_MapTool();

public:
	virtual		HRESULT		Initialize() override;
	virtual		void		Update(f32_t fDeltaTime) override;
	virtual		HRESULT		Render() override;

private:
	unique_ptr<CEditorUI>	m_pEditorUI = { nullptr };

	bool_t								m_bReadyImGui = { false };
private:
	HRESULT Ready_Layer_BackGround(const tchar_t* pLayerTag);
	HRESULT Ready_Layer_GameObject(const tchar_t* pLayerTag);
	HRESULT Ready_Lights();

	HRESULT								Ready_ImGui();
	HRESULT								Begin_ImGui();
	HRESULT								Render_ImGui();
	HRESULT								Shutdown_ImGui();
	void	Sync_SceneView();
public:
	static shared_ptr<CLevel_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END

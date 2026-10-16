#pragma once
#include "Engine_Defines.h"
#include "BlurFilter.h"
NS_BEGIN(Engine)
class CGameObject;
class CRenderer
{
private:
	CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CRenderer() = default;

public:
	HRESULT Initialize(uint32_t iWinSizeX, uint32_t iWinsizeY);
	void	Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject);
	void	Render_GameObject();

	void	Set_Mirror(shared_ptr<CGameObject> pMirror) { m_pMirror = pMirror; }

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	list<shared_ptr<CGameObject>>		m_RenderGroup[ETOUI(RENDERID::END)];

	ComPtr<ID3D11BlendState>			m_pBS = { nullptr };

	ComPtr<ID3D11BlendState>			m_pBS_NoColorWrite = { nullptr };

	ComPtr<ID3D11DepthStencilState>		m_pDSS_Priority = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_NoDepth = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_MarkMirror = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_MarkOccluder = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_Alpha = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_DrawReflection = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_DrawNoDoubleBlend = { nullptr };
	ComPtr<ID3D11DepthStencilState>		m_pDSS_DrawOccludePlayer = { nullptr };

	shared_ptr<CGameObject>				m_pMirror;

	ComPtr<ID3D11RenderTargetView>		m_pSceneRTV;
	ComPtr<ID3D11ShaderResourceView>	m_pSceneSRV;
	ComPtr<ID3D11UnorderedAccessView>	m_pSceneUAV;
	ComPtr<ID3D11VertexShader>			m_pVS_FullScreen;
	ComPtr<ID3D11PixelShader>			m_pPS_FullScreen;

	unique_ptr<CBlurFilter>				m_pBlurFilter;

private:
	void	Render_Priority();
	void	Render_NonAlpha();
	void	Render_OccludedPlayer();
	void	Render_Player();
	void	Render_AlphaPre();
	void	Render_Mirror();
	void	Render_Shadow();
	void	Render_Alpha();
	void	Render_FullScreen();
	void	Render_NonAlpha_UI();
	void	Render_Alpha_UI();

	HRESULT	Ready_BlendState();
	HRESULT	Ready_BlendState_NoColor();
	HRESULT	Ready_Priority_DSS();
	HRESULT	Ready_Alpha_DSS();
	HRESULT	Ready_Mirror_DSS();
	HRESULT	Ready_Occluder_DSS();
	HRESULT	Ready_Shadow_DSS();
	HRESULT	Ready_SceneTarget(uint32_t iWinSizeX, uint32_t iWinsizeY);

public:
	static unique_ptr<CRenderer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, uint32_t iWinSizeX, uint32_t iWinsizeY);
};

NS_END
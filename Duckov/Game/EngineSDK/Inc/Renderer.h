#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CGameObject;
class CRenderer
{
private:
	CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CRenderer() = default;

public:
	HRESULT Initialize();
	void	Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject);
	void	Render_GameObject();

	void	Set_Mirror(shared_ptr<CGameObject> pMirror) { m_pMirror = pMirror; }
	void	Add_ReflectObject(shared_ptr<CGameObject>pObject) { m_ReflectObjects.push_back(pObject); }
	void	Clear_Mirror() { m_pMirror.reset(); m_ReflectObjects.clear(); };

	void	Add_ShadowObject(shared_ptr<CGameObject>pObject) { m_ShadowObjects.push_back(pObject); }
	void	Clear_Shadow() { m_ShadowObjects.clear(); };

private:
	ComPtr<ID3D11Device>				m_pDevice;
	ComPtr<ID3D11DeviceContext>			m_pContext;

	list<shared_ptr<CGameObject>> m_RenderGroup[ETOUI(RENDERID::END)];

	ComPtr<ID3D11BlendState>			m_pBS;

	ComPtr<ID3D11BlendState>			m_pBS_NoColorWrite;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_MarkMirror;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_Alpha;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_DrawReflection;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_DrawNoDoubleBlend;

	shared_ptr<CGameObject>				m_pMirror;
	list<shared_ptr<CGameObject>>		m_ReflectObjects;
	list<shared_ptr<CGameObject>>		m_ShadowObjects;
private:
	void	Render_Priority();
	void	Render_NonAlpha();
	void	Render_AlphaPre();
	void	Render_Mirror();
	void	Render_Shadow();
	void	Render_Alpha();
	void	Render_NonAlpha_UI();
	void	Render_Alpha_UI();

	void	Clear_RenderGroup();


	HRESULT	Ready_BlendState();
	HRESULT	Ready_BlendState_NoColor();
	HRESULT	Ready_Alpha_DSS();
	HRESULT	Ready_Mirror_DSS();
	HRESULT	Ready_Shadow_DSS();

public:
	static unique_ptr<CRenderer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END
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

private:
	void	Render_Priority();
	void	Render_NonAlpha();
	void	Render_Alpha();
	void	Render_NonAlpha_UI();
	void	Render_Alpha_UI();

	void	Clear_RenderGroup();

private:
	list<shared_ptr<CGameObject>> m_RenderGroup[ETOUI(RENDERID::END)];

	ComPtr<ID3D11Device>				m_pDevice;
	ComPtr<ID3D11DeviceContext>			m_pContext;

	ComPtr<ID3D11BlendState>			m_pBS;
public:
	static unique_ptr<CRenderer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END
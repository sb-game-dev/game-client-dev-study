#pragma once

/* 1. 드로우콜되는 객체들을 그리는 순서에 따라 보관한다. */
/* 1_1. 3d의 드로우는 그리는순서를 고려하지않아도 된다.(깊이테스트가 존재하기 때문에 ) */
/* 1_2. 깊이 테스트가 모든 문제를 해결해주지 못한다. and 깊이 테스트때문에 생기는 문제또한 존재하낟. */
/* 2. 결국, 특수한 몇몇객체의 그리는 순서 관리가 필요해진다. */

/* 3. 보관하고 있는 객체들을 순서에 따라 드로우콜(렌더콜, 그린다)해준다. */\

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CRenderer final
{
private:
	CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CRenderer() = default;

public:
	HRESULT Initialize();
	HRESULT Add_RenderGroup(RENDERGROUP eGroupID, shared_ptr<class CGameObject> pRenderObject);
	HRESULT Draw();

private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };

private:

	list<shared_ptr<class CGameObject>>			m_RenderGroups[ETOUI(RENDERGROUP::END)];

private:
	HRESULT Render_Priority();
	HRESULT Render_NonBlend();
	HRESULT Render_Blend();
	HRESULT Render_UI();

public:
	static unique_ptr<CRenderer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END
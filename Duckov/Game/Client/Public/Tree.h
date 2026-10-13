#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CTree : public CGameObject
{
public:
	typedef struct tagTreeDesc : public GAMEOBJECT_DESC
	{

	}TREE_DESC;
private:
	CTree(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CTree() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

private:
	ComPtr<ID3D11GeometryShader>	m_pGS = { nullptr };
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)
	static const uint32_t			m_iTreeCnt = {16};
private:
	HRESULT			Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, ID3D11PixelShader* pPS);

public:
	static shared_ptr<CTree> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END
#pragma once
#include "GameInstance.h"
#include "Transform.h"
#include "Prototype.h"
NS_BEGIN(Engine)
class ENGINE_DLL CGameObject abstract : public CPrototype
{ 
public:
	typedef struct tagGameObjectDesc : public CTransform::TRANSFORM_DESC
	{

	}GAMEOBJECT_DESC;

protected:
	CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CGameObject() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual void		Priority_Update(f32_t fDeltaTime);
	virtual void		Update(f32_t fDeltaTime);
	virtual void		Late_Update(f32_t fDeltaTime);

	virtual HRESULT		Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS) { return S_OK; }
	virtual HRESULT		Render();
	virtual HRESULT		Render_Reflection(const XMMATRIX& matReflect) { return S_OK; }
	virtual HRESULT		Render_Shadow() { return S_OK; }
	virtual HRESULT		Render_Occluded() { return S_OK; }

	// 거울평면의 법선벡터를 a,b,c,d를 반환
	virtual XMVECTOR	Get_MirrorPlane() { return XMVectorZero(); }

	virtual void		Compute_ViewZ();
	virtual	f32_t		Get_ViewZ() { return m_fViewZ; }

	virtual shared_ptr<CTransform>	Get_Transform() { return m_pTransformCom; }

protected:
	ComPtr<ID3D11Buffer>				m_pVB = { nullptr };			// 버텍스 버퍼
	ComPtr<ID3D11Buffer>				m_pIB = { nullptr };			// 인덱스 버퍼
	ComPtr<ID3D11Buffer>				m_pCB = { nullptr };			// 변환 정보를 가지고있는 상수버퍼
	uint32_t							m_iIndexCnt = {};				// 인덱스 개수

	ComPtr<ID3D11InputLayout>			m_pInputLayout = { nullptr };	// 정점 메모리 해석표(FVF의 역할)

	ComPtr<ID3D11VertexShader>			m_pVS = { nullptr };			// 버텍스 셰이더
	ComPtr<ID3D11PixelShader>			m_pPS = { nullptr };			// 픽셀 셰이더
	ComPtr<ID3D11RasterizerState>		m_pRS = { nullptr };			// 레스터라이저

	ComPtr<ID3D11ShaderResourceView>	m_pSRV = { nullptr };
	ComPtr<ID3D11SamplerState>			m_pSampler = { nullptr };

	shared_ptr<CTransform>				m_pTransformCom = { nullptr };

	map<const wstring_t, shared_ptr<CComponent>>		m_Components;

	f32_t				m_fViewZ = {};

	MATERIAL			m_tMaterial = {};

protected:
	shared_ptr<CComponent> Find_Component(const wstring_t& strComponentTag);

	template<typename T>
	HRESULT Add_Component(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag,
		const wstring_t& strComponentTag, shared_ptr<T>& pOut, void* pArg = nullptr)
	{
		if (nullptr != Find_Component(strComponentTag))
			return E_FAIL;
		pOut = dynamic_pointer_cast<T>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
		if (nullptr == pOut)
			return E_FAIL;

		m_Components.emplace(strComponentTag, pOut);
		return S_OK;
	}

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;
};
NS_END

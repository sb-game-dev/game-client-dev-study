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

	virtual void			Set_Dead() { m_bDead = true; }
	virtual bool_t			Is_Dead()const { return m_bDead; }
	virtual void			Remove_Component(const wstring_t& strComponentTag) { m_Components.erase(strComponentTag); }
	shared_ptr<CComponent>	Find_Component(const wstring_t& strComponentTag);

protected:
	shared_ptr<CConstantBuffer>			m_pCB = { nullptr };			
	CB_PER_OBJECT						m_tCBData = {};					

	ComPtr<ID3D11RasterizerState>		m_pRS = { nullptr };			

	shared_ptr<CTransform>				m_pTransformCom = { nullptr };

	map<const wstring_t, shared_ptr<CComponent>>		m_Components;

	f32_t				m_fViewZ = {};


	bool_t				m_bDead = { false };

protected:
	virtual		bool_t		Is_InFrustum();
	virtual		bool_t		Is_BoxInFrustum(const BoundingBox& tLocalBox, const matrix_t& matWorld);

	virtual		HRESULT		Bind_Shader() { return S_OK; }
	virtual		HRESULT		Bind_ShaderResources() { return S_OK; }

protected:

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

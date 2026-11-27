#pragma once
#include "Client_Defines.h"
#include "ContainerObject.h"

NS_BEGIN(Client)
class CTargetDummy : public CContainerObject
{
public:
	typedef struct tagTargetDummyDesc : public CONTAINEROBJECT_DESC
	{
		const wchar_t* pHelmetTag = { nullptr };
		const wchar_t* pArmorTag = { nullptr };
	}TARGETDUMMY_DESC;
private:
	CTargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CTargetDummy() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

public:
	virtual void	TriggerEnter(shared_ptr<class CCollider> pOtherCollider)override;
	virtual void	Take_Damage(const DAMAGE_DESC& Desc)override;


private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)
	weak_ptr<class CHill>			m_pHill;

	float4x4_t						m_HelmetSocketmatrix = {};
	float4x4_t						m_ArmorSocketmatrix = {};
	
private:
	shared_ptr<class CUI_HpBar>			m_pHpBar = { nullptr };


	shared_ptr<CCube_Collider>			m_pCube_Collider = { nullptr };
	shared_ptr<class CBody_TargetDummy> m_pBodyTargetDummy = { nullptr };
	shared_ptr<class CHelmet_TargetDummy> m_pHelmetTargetDummy = { nullptr };
	shared_ptr<class CArmor_TargetDummy> m_pArmorTargetDummy = { nullptr };

	const wchar_t* m_pHelmetTag = { nullptr };
	const wchar_t* m_pArmorTag = { nullptr };

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_PartObjects();
;
public:
	static shared_ptr<CTargetDummy> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END
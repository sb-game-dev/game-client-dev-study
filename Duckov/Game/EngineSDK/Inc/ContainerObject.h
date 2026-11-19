#pragma once
#include "GameObject.h"
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class ENGINE_DLL CContainerObject : public CGameObject
{
public:
	typedef struct tagContainerObjectDesc : public CGameObject::GAMEOBJECT_DESC
	{

	}CONTAINEROBJECT_DESC;

protected:
	CContainerObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CContainerObject() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual void		Priority_Update(f32_t fDeltaTime)override;
	virtual void		Update(f32_t fDeltaTime)override;
	virtual void		Late_Update(f32_t fDeltaTime)override;
	virtual HRESULT		Render()override;

protected:
	map<const wstring_t, shared_ptr<class CPartObject>>		m_PartObjects;

protected:
	shared_ptr<class CPartObject>	Find_PartObect(const wstring_t& strPartObjectTag);
	HRESULT Add_PartObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, const wstring_t& strPartTag, void* pArg);

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;

};

NS_END
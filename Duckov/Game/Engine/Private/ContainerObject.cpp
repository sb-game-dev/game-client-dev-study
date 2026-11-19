#include "ContainerObject.h"
#include "PartObject.h"
CContainerObject::CContainerObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{ pDevice, pContext }
{
}

HRESULT CContainerObject::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CContainerObject::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	if (nullptr == pArg)
		return S_OK;
	auto	pDesc = static_cast<CONTAINEROBJECT_DESC*>(pArg);

	return S_OK;
}

void CContainerObject::Priority_Update(f32_t fDeltaTime)
{
	__super::Priority_Update(fDeltaTime);
}

void CContainerObject::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
}

void CContainerObject::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

HRESULT CContainerObject::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return S_OK;
}

shared_ptr<class CPartObject> CContainerObject::Find_PartObect(const wstring_t& strPartObjectTag)
{
	auto iter = m_PartObjects.find(strPartObjectTag);
	if (m_PartObjects.end() == iter)
		return nullptr;

	return iter->second;
}

HRESULT CContainerObject::Add_PartObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, const wstring_t& strPartTag, void* pArg)
{
	if (nullptr != Find_PartObect(strPartTag))
		return E_FAIL;

	auto pPartObject = static_pointer_cast<CPartObject>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
	if (nullptr == pPartObject)
		return E_FAIL;

	m_PartObjects.emplace(strPartTag, pPartObject);
	return S_OK;
}

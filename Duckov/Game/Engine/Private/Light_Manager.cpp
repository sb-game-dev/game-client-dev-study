#include "Light_Manager.h"
#include "Light.h"
CLight_Manager::CLight_Manager()
{
}
void CLight_Manager::Priority_Update(f32_t fDeltaTime)
{
	for (auto& pLight : m_Lights)
	{
		if (pLight.second != nullptr)
			pLight.second->Priority_Update(fDeltaTime);
	}
}
void CLight_Manager::Update(f32_t fDeltaTime)
{
	for (auto& pLight : m_Lights)
	{
		if (pLight.second != nullptr)
			pLight.second->Update(fDeltaTime);
	}
}
void CLight_Manager::Late_Update(f32_t fDeltaTime)
{
	for (auto& pLight : m_Lights)
	{
		if (pLight.second != nullptr)
			pLight.second->Late_Update(fDeltaTime);
	}
}
void CLight_Manager::AddLight(const wstring_t& strLightTag, shared_ptr<CLight> pLight)
{
	if (nullptr != Find_Light(strLightTag))
		return;
	m_Lights.emplace(strLightTag, pLight);
}
shared_ptr<CLight> CLight_Manager::Find_Light(const wstring_t& strLightTag)
{
	auto iter = m_Lights.find(strLightTag);
	if (iter == m_Lights.end())
		return nullptr;
	return iter->second;
}
unique_ptr<CLight_Manager> CLight_Manager::Create()
{
	return unique_ptr<CLight_Manager>(new CLight_Manager());
}

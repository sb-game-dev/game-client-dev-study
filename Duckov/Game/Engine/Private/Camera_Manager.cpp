#include "Camera_Manager.h"
#include "Camera.h"
CCamera_Manager::CCamera_Manager()
{
}

void CCamera_Manager::Add_Camera(const wstring_t& strCameraTag, shared_ptr<CCamera> pCamera)
{
	if (nullptr != Find_Camera(strCameraTag))
		return;
	m_pCameras.emplace(strCameraTag, pCamera);
}

void CCamera_Manager::Set_MainCamera(const wstring_t& strCameraTag)
{
	auto pCamera = Find_Camera(strCameraTag);
	if (nullptr == pCamera)
		return;
	m_pMainCamera = pCamera;
}

void CCamera_Manager::Priority_Update(f32_t fDeltaTime)
{
	if (m_pMainCamera)
		m_pMainCamera->Priority_Update(fDeltaTime);
}

void CCamera_Manager::Update(f32_t fDeltaTime)
{
	if (m_pMainCamera)
		m_pMainCamera->Update(fDeltaTime);
}

void CCamera_Manager::Late_Update(f32_t fDeltaTime)
{
	if (m_pMainCamera)
		m_pMainCamera->Late_Update(fDeltaTime);
}

HRESULT CCamera_Manager::Bind()
{
	if (nullptr == m_pMainCamera)
		return E_FAIL;
	if(FAILED(m_pMainCamera->Bind()))
		return E_FAIL;

	return S_OK;
}

shared_ptr<CCamera> CCamera_Manager::Find_Camera(const wstring_t& strCameraTag)
{
	auto iter = m_pCameras.find(strCameraTag);
	if (iter == m_pCameras.end())
		return nullptr;
	return iter->second;
}

unique_ptr<CCamera_Manager> CCamera_Manager::Create()
{
	return unique_ptr<CCamera_Manager>(new CCamera_Manager());
}

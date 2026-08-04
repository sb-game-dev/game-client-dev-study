#include "pch.h"
#include "CMainApp.h"
#include "CLogo.h"
#include "CProtoMgr.h"
#include "CFontMgr.h"
#include "CDInputMgr.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"
#include "CCollisionMgr.h"
#include "CRenderer.h"
#include "CLightMgr.h"
CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pGraphicDev(nullptr)
	, m_pManagementClass(CManagement::GetInstance())
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{	
	if (FAILED(Ready_DefaultSetting(&m_pGraphicDev)))
		return E_FAIL; 

	if (FAILED(Ready_Scene(m_pGraphicDev)))
		return E_FAIL;

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG


	return S_OK;
}

int CMainApp::Update_MaintApp(const float& fTimeDelta)
{
	CKeyMgr::GetInstance()->KeyUpdate();
	CDInputMgr::GetInstance()->Update_InputDev();

	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
	m_pManagementClass->LateUpdate_Scene(fTimeDelta);
}

void CMainApp::Render_MainApp()
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	
	if (CCameraMgr::GetInstance()->GetCameraCnt() > 0)
	{
		D3DVIEWPORT9 oldViewPort;
		m_pGraphicDev->GetViewport(&oldViewPort);
		D3DVIEWPORT9 ViewPort;
		_matrix matView;

		//////////////////////일반 맵/////////////////////////////////////////////
		ViewPort = CCameraMgr::GetInstance()->GetCameraViewPort(PLAYER1);
		m_pGraphicDev->SetViewport(&ViewPort);
		
		matView = CCameraMgr::GetInstance()->GetCameraView(PLAYER1);
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
		m_pManagementClass->Render_Scene(m_pGraphicDev);

		//////////////////////미니 맵/////////////////////////////////////////////
		ViewPort = CCameraMgr::GetInstance()->GetCameraViewPort(MAP);
		m_pGraphicDev->SetViewport(&ViewPort);
		
		m_pDeviceClass->Render_Begin(D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
		matView = CCameraMgr::GetInstance()->GetCameraView(MAP);
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
		m_pManagementClass->Render_Scene(m_pGraphicDev);

		//////////////////////뷰포트 초기화/////////////////////////////////////////////
		m_pGraphicDev->SetViewport(&oldViewPort);
	}
	else
	{
		m_pManagementClass->Render_Scene(m_pGraphicDev);
	}

	m_pDeviceClass->Render_End();


}

HRESULT CMainApp::Ready_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	if (FAILED(CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass)))
		return E_FAIL;

	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 텍스처 필터
	(*ppGraphicDev)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	(*ppGraphicDev)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// 폰트 추가

	if(FAILED(CFontMgr::GetInstance()->Ready_Font(m_pGraphicDev, L"Font_Default", L"견명조", 20, 15, FW_HEAVY)))
		return E_FAIL;

	if (FAILED(CFontMgr::GetInstance()->Ready_Font(m_pGraphicDev, L"Font_Jinji", L"궁서", 20, 15, FW_THIN)))
		return E_FAIL;

	// DInputMgr의 멤버들 객체 생성
	if (FAILED(CDInputMgr::GetInstance()->Ready_InputDev(g_hInst, g_hWnd)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::CScene* pLogo = CLogo::Create(pGraphicDev);

	if (nullptr == pLogo)
		return E_FAIL;

	if (FAILED(m_pManagementClass->Set_Scene(pLogo)))
	{
		Safe_Release(pLogo);

		MSG_BOX("Logo Create Failed");
		return E_FAIL;
	}
	
	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		MSG_BOX("MainApp Create Failed");
		Safe_Release(pMainApp);
		return nullptr;
	}

	return pMainApp;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);

	CLightMgr::DestroyInstance();
	CRenderer::DestroyInstance();
	CCollisionMgr::DestroyInstance();
	CCameraMgr::DestroyInstance();
	CDInputMgr::DestroyInstance();
	CKeyMgr::DestroyInstance();
	CFontMgr::DestroyInstance();
	CProtoMgr::DestroyInstance();
	CFrameMgr::DestroyInstance();
	CTimerMgr::DestroyInstance();
	m_pManagementClass->DestroyInstance();
	m_pDeviceClass->DestroyInstance();
}

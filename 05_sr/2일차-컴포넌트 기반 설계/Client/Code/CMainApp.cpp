#include "pch.h"
#include "CMainApp.h"


const DWORD Vertex::FVF = D3DFVF_XYZ;
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
CMainApp::CMainApp()
	: m_pDeviceClass(nullptr), m_pGraphicDev(nullptr)
	, m_pManagementClass(CManagement::GetInstance())
{
	m_fRotateY = 0.f;
	m_fRotateX = 0.f;
	m_vCameraPos = { 0,0,-5 };

	m_vMousePos = { 0,0,0 };
	m_vPreMousePos = { 0,0,0 };

	m_vCameraDir = { 0,0,1 };
	m_vCameraLook = { 0,0,1 };
	m_fCameraMoveSpeed = 0.1f;
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass)))
		return E_FAIL;

	m_pDeviceClass->AddRef();

	m_pGraphicDev = m_pDeviceClass->Get_GraphicDev();
	m_pGraphicDev->AddRef();

	m_pManagementClass->Set_Scene(NULL);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

int CMainApp::Update_MainApp(const float& fTimeDelta)
{
	//m_pManagementClass->Update_Scene(fTimeDelta);
	KeyInput();
	D3DXMATRIX matRotY, matRotX,matRotXY;
	D3DXMatrixRotationX(&matRotX, m_fRotateX);
	D3DXMatrixRotationY(&matRotY, m_fRotateY);
	matRotXY = matRotX * matRotY;
	D3DXVec3TransformNormal(&m_vCameraDir, &m_vCameraLook, &matRotXY);


	D3DXVECTOR3 position = m_vCameraPos;
	D3DXVECTOR3 target = m_vCameraPos + m_vCameraDir;
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMATRIX	V;

	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	return 0;
}

void CMainApp::LateUpdate_MainApp(const float& fTimeDelta)
{
	//m_pManagementClass->LateUpdate_Scene(fTimeDelta);
}

void CMainApp::Render_MainApp()
{
	m_pDeviceClass->Render_Begin(D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//m_pManagementClass->Render_Scene(m_pGraphicDev);

	//RenderCube();
	//RenderCube2();
	//RenderTriangle();
	RenderPyramid();
	m_pDeviceClass->Render_End();
}

void CMainApp::RenderCube()
{
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9* IB = 0;

	m_pGraphicDev->CreateVertexBuffer(8 * sizeof(ColorVertex), 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	ColorVertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = ColorVertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[1] = ColorVertex(-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[2] = ColorVertex(1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[3] = ColorVertex(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[4] = ColorVertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[5] = ColorVertex(-1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[6] = ColorVertex(1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[7] = ColorVertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));

	for (int i = 0; i < 8; i++)
		vertices[i]._x -= 2.f;

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	//전면
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	//후면
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// 왼쪽 측면
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// 오른쪽 측면
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// 상단
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// 하단
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();


	m_vMousePos.x = (GetMouse().x - WINCX * 0.5f) / (WINCX * 0.1f);
	m_vMousePos.y = -(GetMouse().y - WINCY * 0.5f) / (WINCY * 0.1f);



	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		WINCX / WINCY,
		1.f,
		1000.f
	);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// D3DFILL_POINT(점),D3DFILL_WIREFRAME(선),D3DFILL_SOLID(면)

	D3DXMATRIX Rx, Ry;

	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(ColorVertex));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(ColorVertex::FVF);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, 8, 0, 12);
}
void CMainApp::RenderCube2()
{
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9* IB = 0;

	m_pGraphicDev->CreateVertexBuffer(8 * sizeof(ColorVertex), 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	ColorVertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = ColorVertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[1] = ColorVertex(-1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[2] = ColorVertex(1.0f, 1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[3] = ColorVertex(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[4] = ColorVertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[5] = ColorVertex(-1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[6] = ColorVertex(1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[7] = ColorVertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));

	for (int i = 0; i < 8; ++i)
		vertices[i]._x += 1.f;

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	//전면
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	//후면
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// 왼쪽 측면
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// 오른쪽 측면
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// 상단
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// 하단
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		WINCX / WINCY,
		1.f,
		1000.f
	);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// D3DFILL_POINT(점),D3DFILL_WIREFRAME(선),D3DFILL_SOLID(면)

	D3DXMATRIX Rx, Ry;


	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(ColorVertex));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(ColorVertex::FVF);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, 8, 0, 12);
}

void CMainApp::RenderPyramid()
{
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9* IB = 0;

	m_pGraphicDev->CreateVertexBuffer(5 * sizeof(ColorVertex), 0, D3DFVF_XYZ, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(18 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	ColorVertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = ColorVertex(-1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[1] = ColorVertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[2] = ColorVertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[3] = ColorVertex(1.0f, -1.0f, -1.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[4] = ColorVertex(0.f, 1.0f, 0.f, D3DCOLOR_XRGB(0, 0, 255));

	//for (int i = 0; i < 5; ++i)
	//	vertices[i]._y += 3.f;

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	//전면
	indices[0] = 0; indices[1] = 4; indices[2] = 3;

	//후면
	indices[3] = 2; indices[4] = 4; indices[5] = 1;

	//왼쪽 측면
	indices[6] = 1; indices[7] = 4; indices[8] = 0;

	//오른쪽 측면
	indices[9] = 3; indices[10] = 4; indices[11] = 2;

	// 하단
	indices[12] = 1; indices[13] = 0; indices[14] = 2;
	indices[15] = 2; indices[16] = 0; indices[17] = 3;

	IB->Unlock();

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		WINCX / WINCY,
		1.f,
		1000.f
	);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// D3DFILL_POINT(점),D3DFILL_WIREFRAME(선),D3DFILL_SOLID(면)

	D3DXMATRIX Rx, Ry;


	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(ColorVertex));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(ColorVertex::FVF);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, 5, 0, 6);
}

void CMainApp::RenderTriangle()
{
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	D3DXMATRIX	world;

	IDirect3DVertexBuffer9* Triangle = 0;

	m_pGraphicDev->CreateVertexBuffer(
		3 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle,
		0);

	ColorVertex* v;
	Triangle->Lock(0, 0, (void**)&v, 0);

	v[0] = ColorVertex(-1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
	v[1] = ColorVertex( 0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
	v[2] = ColorVertex( 1.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));

	Triangle->Unlock();

	D3DXVECTOR3 position(0, 0, -1.1f);
	D3DXVECTOR3 target(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMATRIX	V;
	
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		WINCX / WINCY,
		1.0f,
		1000.f
	);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);

	m_pGraphicDev->SetFVF(ColorVertex::FVF);
	m_pGraphicDev->SetStreamSource(0, Triangle, 0, sizeof(ColorVertex));



	//D3DXMatrixTranslation(&world, -1.25f, 0.0f, 0.0f);

	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void CMainApp::KeyInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		m_fRotateX -= D3DXToRadian(1.f);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_fRotateX += D3DXToRadian(1.f);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fRotateY -= D3DXToRadian(1.f);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fRotateY += D3DXToRadian(1.f);
	}
	if (GetAsyncKeyState('W'))
	{
		//D3DXVECTOR3 vCamMouseDelta = m_vMousePos - m_vCameraPos;
		//D3DXVec3Normalize(&vCamMouseDelta, &vCamMouseDelta);
		//m_vCameraPos += vCamMouseDelta * 0.1f;
		m_vCameraPos += m_vCameraDir * m_fCameraMoveSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		//D3DXVECTOR3 vCamMouseDelta = m_vMousePos - m_vCameraPos;
		//D3DXVec3Normalize(&vCamMouseDelta, &vCamMouseDelta);
		//m_vCameraPos -= vCamMouseDelta * 0.1f;
		m_vCameraPos -= m_vCameraDir * m_fCameraMoveSpeed;
	}
	//if (GetAsyncKeyState('A'))
	//{
	//	m_vCameraPos.x -= m_fCameraMoveSpeed;
	//
	//}
	//if (GetAsyncKeyState('D'))
	//{
	//	m_vCameraPos.x += m_fCameraMoveSpeed;
	//}
}

D3DXVECTOR3 CMainApp::GetMouse()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
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
	m_pManagementClass->DestroyInstance();
	m_pDeviceClass->DestroyInstance();

	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);

	CFrameMgr::DestroyInstance();
	CTimerMgr::DestroyInstance();
}

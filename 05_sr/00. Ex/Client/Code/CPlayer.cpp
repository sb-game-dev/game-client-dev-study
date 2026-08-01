#include "pch.h"
#include "CPlayer.h"
#include "CProtoMgr.h"
#include "CBullet.h"
#include "CManagement.h"
#include "CKeyMgr.h"
#include "CDInputMgr.h"
#include "Engine_Function.h"
#include "CCameraMgr.h"
#include "CRenderer.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;

	m_pTransformCom->m_vInfo[INFO_POS] = { 50,50,-50 };
	m_pTransformCom->m_vScale = { 1,1,1 };
	m_pTransformCom->Rotation(ROT_X, 90);
	m_fNormalSpeed = 10.f;
	m_fBoostSpeed = 20.f;
	m_fSpeed = m_fNormalSpeed;
	m_vGravity = { 0, -9.8,0 };
	m_fJumpPower = 30.f;

	m_vTargetPos = m_pTransformCom->m_vInfo[INFO_POS];

	m_eMoveState = GROUND;
	m_iBulletCnt = 0;

	m_pColliderCom->SetHalfSize({1,1,2});
	m_pColliderCom->SetCenter({ 50,50,-50 });

	CRenderer::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return S_OK;
}

_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	m_pTransformCom->m_ePreMoveState = m_pTransformCom->m_eMoveState;

	Key_Input2(fTimeDelta);


	if (m_pTransformCom->m_eMoveState == JUMP || m_pTransformCom->m_eMoveState == FALL)
	{
		m_vGravity.y -= 20 * fTimeDelta;
		m_pTransformCom->Move_Pos(&m_vGravity, 3, fTimeDelta);
	}

	return iExit;
}

void CPlayer::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

	//Mouse_Input(fTimeDelta);
	//MoveToTarget(fTimeDelta);
	CTerrainTex* pTerrainCom = dynamic_cast<CTerrainTex*>
		(CManagement::GetInstance()->Get_Component(ID_STATIC, L"GameLogic_Layer", L"Terrain", L"Com_Buffer"));

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	if (vPos.x > 0 && vPos.x < 128 && vPos.z < 0 && vPos.z > -128)
	{
		float fY = pTerrainCom->GetHeight_UsePlane(vPos.x, vPos.z);

		if ((m_pTransformCom->m_eMoveState == JUMP || m_pTransformCom->m_eMoveState == FALL) && vPos.y < fY )
		{
			m_pTransformCom->m_eMoveState = GROUND;
		}
		if(m_pTransformCom->m_eMoveState == GROUND)
			m_pTransformCom->m_vInfo[INFO_POS].y = fY + 2;
	}
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	m_pColliderCom->SetCenter(vPos);


	cout <<"MoveState: " << m_pTransformCom->m_eMoveState << endl;
	//cout << m_pTransformCom->m_vInfo[INFO_POS].x << "\t" << m_pTransformCom->m_vInfo[INFO_POS].y << "\t" << m_pTransformCom->m_vInfo[INFO_POS].z << endl;
}

void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());
	m_pGraphicDev->SetTexture(0, NULL);
	m_pBufferCom->Render_Buffer();
}

HRESULT CPlayer::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;

	// RcCol
	pComponent = m_pBufferCom = dynamic_cast<CPyramidCol*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Pyramid", this));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	/////////////////////////////////////////////////////////////////
	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform", this));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	// Collider
	pComponent = m_pColliderCom = dynamic_cast<CCollider*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Collider", this));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	_vec3	vLook;
	m_pTransformCom->Get_Info(INFO_UP, &vLook);

	if (GetAsyncKeyState(VK_UP))
	{
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), m_fSpeed, fTimeDelta);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), -m_fSpeed, fTimeDelta);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pTransformCom->Rotation(ROT_Y, -180.f * fTimeDelta);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_pTransformCom->Rotation(ROT_Y, 180.f * fTimeDelta);
	}

	if (GetAsyncKeyState('W'))
	{
		m_pTransformCom->Rotation(ROT_X, -80.f * fTimeDelta);
	}

	if (GetAsyncKeyState('S'))
	{
		m_pTransformCom->Rotation(ROT_X, 80.f * fTimeDelta);
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_SPACE))
	{
		Shoot();
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		m_fSpeed = m_fBoostSpeed;
	}
	else
	{
		m_fSpeed = m_fNormalSpeed;
	}
}

void CPlayer::Key_Input2(const _float& fTimeDelta)
{
	_vec3	vCameraLook;
	_vec3	vPlayerLook;
	_vec3	m_vPlayerRight;

	CTransform* pCameraTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Environment_Layer", L"Camera", L"Com_Transform"));
	
	vCameraLook = pCameraTransformCom->m_vInfo[INFO_LOOK];
	vPlayerLook = m_pTransformCom->m_vInfo[INFO_UP];

	vCameraLook.y = 0;
	vPlayerLook.y = 0;
	bool bKeyInput = false;
	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_W))
	{
		bKeyInput = true;
		_vec3 cross;
		D3DXVec3Cross(&cross, &vPlayerLook, &vCameraLook);

		float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
										 D3DXVec3Normalize(&vCameraLook, &vCameraLook)));
		
		if (D3DXToDegree(fAngle) > 1)
		{
			if (cross.y < 0) fAngle *= -1;
			m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
		}
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vCameraLook, &vCameraLook), m_fSpeed, fTimeDelta);
	}

	else if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_S))
	{
		bKeyInput = true;
		_vec3 cross;
		D3DXVec3Cross(&cross, &vPlayerLook, &vCameraLook);

		float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
										 D3DXVec3Normalize(&vCameraLook, &vCameraLook)));

		if (D3DXToDegree(fAngle) > 1)
		{
			if (cross.y < 0) fAngle *= -1;
			m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
		}
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vCameraLook, &vCameraLook), -m_fSpeed, fTimeDelta);
	}

	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_D))
	{
		memcpy(&m_vPlayerRight, &pCameraTransformCom->m_vInfo[INFO_RIGHT], sizeof(_vec3));
		m_vPlayerRight.y = 0;

		if (bKeyInput == false)
		{
			_vec3 cross;
			D3DXVec3Cross(&cross, &vPlayerLook, &m_vPlayerRight);
			float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
				D3DXVec3Normalize(&m_vPlayerRight, &m_vPlayerRight)));

			if (D3DXToDegree(fAngle) > 1)
			{
				if (cross.y < 0) fAngle *= -1;
				m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
			}
		}
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&m_vPlayerRight, &m_vPlayerRight), m_fSpeed, fTimeDelta);
	}

	else if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_A))
	{
		memcpy(&m_vPlayerRight, &pCameraTransformCom->m_vInfo[INFO_RIGHT], sizeof(_vec3));
		m_vPlayerRight.y = 0;
		m_vPlayerRight *= -1;

		if (bKeyInput == false)
		{
			_vec3 cross;
			D3DXVec3Cross(&cross, &vPlayerLook, &m_vPlayerRight);
			float fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vPlayerLook, &vPlayerLook),
				D3DXVec3Normalize(&m_vPlayerRight, &m_vPlayerRight)));

			if (D3DXToDegree(fAngle) > 1)
			{
				if (cross.y < 0) fAngle *= -1;
				m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
			}
		}
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&m_vPlayerRight, &m_vPlayerRight), m_fSpeed, fTimeDelta);
	}


	if (CDInputMgr::GetInstance()->Get_KeyDown(DIK_Q))
	{
		Shoot();
	}
	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_SPACE))
	{
		if (m_pTransformCom->m_eMoveState == GROUND || m_pTransformCom->m_eMoveState == RIDING)
		{
			m_pTransformCom->m_eMoveState = JUMP;
			ReSetGravity();
			m_vGravity.y += m_fJumpPower;
		}
	}
	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_LSHIFT))
	{
		m_fSpeed = m_fBoostSpeed;
	}
	else
	{
		m_fSpeed = m_fNormalSpeed;
	}
}

void CPlayer::Mouse_Input(const _float& fTimeDelta)
{
	//if(CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	if (CDInputMgr::GetInstance()->Get_DIMouseState(DIM_RB))
	{
		m_vTargetPos = GetRayPickPos();
	}

	// 총 발사 및 점프
	if (CDInputMgr::GetInstance()->Get_KeyDown(DIK_Q))
	{
		Shoot();
	}
	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_SPACE))
	{
		if (m_pTransformCom->m_eMoveState == GROUND || m_pTransformCom->m_eMoveState == RIDING)
		{
			m_pTransformCom->m_eMoveState = JUMP;
			ReSetGravity();
			m_vGravity.y += m_fJumpPower;
		}
	}

	if (CDInputMgr::GetInstance()->Get_DIKeyState(DIK_LSHIFT))
	{
		m_fSpeed = m_fBoostSpeed;
	}
	else
	{
		m_fSpeed = m_fNormalSpeed;
	}
}


void CPlayer::Shoot()
{
	_vec3 vDir;
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO_UP, &vDir);
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	vPos += vDir * 4;
	CGameObject* pBullet = CBullet::Create(m_pGraphicDev, vPos, vDir);

	CLayer* pLayer = CManagement::GetInstance()->Get_Layer(L"Environment_Layer");
	if (pLayer == nullptr)
	{
		MSG_BOX("Shoot and Layer Create Failed");
		return;
	}
	++m_iBulletCnt;

	const _tchar* szBuff = L"Bullet" + m_iBulletCnt;
	pLayer->Add_GameObject(szBuff, pBullet);
}

void CPlayer::MoveToTarget(const _float& fTimeDelta)
{

	_vec3 vMoveDir = m_vTargetPos - m_pTransformCom->m_vInfo[INFO_POS];
	vMoveDir.y = 0;
	if (D3DXVec3Length(&vMoveDir) > 0.1f)
	{
		D3DXVec3Normalize(&vMoveDir, &vMoveDir);
		m_pTransformCom->Move_Pos(&vMoveDir, m_fSpeed, fTimeDelta);
		//if (D3DXVec3Length(&vMoveDir) > m_fSpeed * fTimeDelta)
		//{
		//	m_pTransformCom->Move_Pos(&vMoveDir, m_fSpeed, fTimeDelta);
		//}
		//else
		//{
		//	m_pTransformCom->Move_Pos(&vMoveDir, D3DXVec3Length(&vMoveDir) / fTimeDelta, fTimeDelta);
		//}
		_vec3 vPlayerLook;
		vPlayerLook = m_pTransformCom->m_vInfo[INFO_UP];
		vPlayerLook.y = 0;
		D3DXVec3Normalize(&vPlayerLook, &vPlayerLook);

		_vec3 cross;
		D3DXVec3Cross(&cross, &vPlayerLook, &vMoveDir);

		float fAngle = acosf(D3DXVec3Dot(&vPlayerLook, &vMoveDir));
		if (D3DXToDegree(fAngle) > 1)
		{
			if (cross.y < 0) fAngle *= -1;
			m_pTransformCom->Rotation(ROT_Y, D3DXToDegree(fAngle));
		}
	}



}

_vec3 CPlayer::GetRayPickPos()
{//1. 마우스 위치 가져오기
	_vec3 vMousePos = GetMouse(g_hWnd);

	// 2. 광선 위치 및 방향 계산(아직 view 스페이스)
	D3DVIEWPORT9 vp = CCameraMgr::GetInstance()->GetCameraViewPort(PLAYER1);

	_matrix proj = CCameraMgr::GetInstance()->GetCameraProj(PLAYER1);

	RAY ray = CalPickingRay(m_pGraphicDev, vp, proj, vMousePos.x, vMousePos.y);

	// 3. 광선을 view -> world로 변환
	D3DXMATRIX view = CCameraMgr::GetInstance()->GetCameraView(PLAYER1);

	D3DXMATRIX viewInverse;
	D3DXMatrixInverse(&viewInverse, 0, &view);

	TransformRay(&ray, &viewInverse);

	// 4. 피킹 좌표 가져오기
	float u, v;
	float dist;
	_vec3	vPickPos;
	if (m_vTerrainVertex.empty())
	{
		CTerrainTex* pTerrainCom = dynamic_cast<CTerrainTex*>
			(CManagement::GetInstance()->Get_Component(ID_STATIC, L"Environment_Layer", L"Terrain", L"Com_Buffer"));

		m_vTerrainVertex = pTerrainCom->GetVertex();
		m_vTerrainIndex = pTerrainCom->GetIndex();
	}
	for (auto i : m_vTerrainIndex)
	{
		if (D3DXIntersectTri(
			&m_vTerrainVertex[i.x],
			&m_vTerrainVertex[i.y],
			&m_vTerrainVertex[i.z],
			&ray.vOrig,
			&ray.vDir,
			&u,
			&v,
			&dist))
		{
			vPickPos =
				m_vTerrainVertex[i.x]
				+ u * (m_vTerrainVertex[i.y] - m_vTerrainVertex[i.x])
				+ v * (m_vTerrainVertex[i.z] - m_vTerrainVertex[i.x]);
			return vPickPos;
			// 5. 이동
		}
	}
	return { 0,0,0 };
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pPlayer = new CPlayer(pGraphicDev);

	if (FAILED(pPlayer->Ready_GameObject()))
	{
		Safe_Release(pPlayer);
		MSG_BOX("pPlayer Create Failed");
		return nullptr;
	}

	return pPlayer;
}

void CPlayer::Free()
{
	CGameObject::Free();
}


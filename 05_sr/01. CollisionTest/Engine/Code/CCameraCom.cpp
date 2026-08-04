#include "CCameraCom.h"

CCameraCom::CCameraCom()
{
}

CCameraCom::CCameraCom(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CCameraCom::CCameraCom(const CCameraCom& rhs)
	:CComponent(rhs)
{
}

CCameraCom::~CCameraCom()
{
}

_int CCameraCom::Update_Component(const _float& fTimeDelta)
{
	return 0;
}


void CCameraCom::LateUpdate_Component()
{
	_matrix matView, matProj;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(m_fFov), (_float)WINCX / WINCY, 0.1f, 1000.f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}
void CCameraCom::MouseControl(_vec3* vPlayerPos, _vec3* vPlayerLook, _vec3* vMousePos)
{
	// 0. 플레이어 위치 가져오기
	_vec3	_vPlayerPos = *vPlayerPos;

	// 1. 마우스 위치 가져오기
	_vec3	_vMousePos = *vMousePos;
	_vMousePos.x -= WINCX * 0.5f;
	_vMousePos.y -= WINCY * 0.5f;

	// 2. At 이동
	m_vAt = { 0,0,1 };

	// 3. At 회전(공전)
	_matrix		matRot[ROT_END];

	FLOAT		fRotX = D3DXToRadian(_vMousePos.y) / 10;
	FLOAT		fRotY = D3DXToRadian(_vMousePos.x) / 10;

	if (fRotX > 1.5)
		fRotX = 1.5;
	if (fRotX < -1.5)
		fRotX = -1.5;

	D3DXMatrixRotationX(&matRot[ROT_X], fRotX);
	D3DXMatrixRotationY(&matRot[ROT_Y], fRotY);

	for (_uint i = 0; i < ROT_Z; ++i)
		D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRot[i]);

	// 4. Eye 이동
	m_vEye = _vPlayerPos - m_vAt * 10;

	// 5. At 이동
	m_vAt += m_vEye;

	// 6. 플레이어 Look 설정
	*vPlayerLook = m_vAt;
}


HRESULT CCameraCom::Ready_CameraCom()
{
	m_vEye = { 0,5,-10 };
	m_vAt = { 0,0,0 };
	m_vUp = { 0,1,0 };

	m_fFov = 60.f;
	return S_OK;
}

CCameraCom* CCameraCom::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCameraCom* pCameraCom = new CCameraCom(pGraphicDev);

	if (FAILED(pCameraCom->Ready_CameraCom()))
	{
		Safe_Release(pCameraCom);
		MSG_BOX("pCameraCom Create Failed");
		return nullptr;
	}

	return pCameraCom;
}

CComponent* CCameraCom::Clone()
{
	return new CCameraCom(*this);
}

void CCameraCom::Free()
{
	CComponent::Free();
}
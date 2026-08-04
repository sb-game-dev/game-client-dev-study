#include "CPyramidCol.h"

CPyramidCol::CPyramidCol()
{
}

CPyramidCol::CPyramidCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CPyramidCol::CPyramidCol(const CPyramidCol& rhs)
	:CVIBuffer(rhs)
{
}

CPyramidCol::~CPyramidCol()
{
}

HRESULT	CPyramidCol::Ready_Buffer()
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 5;
	m_dwTriCnt = 6;
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;

	VTXCOL* pVertex = NULL;

	// &pVertex : 버텍스 버퍼에 저장된 버텍스 중 첫번째 버텍스의 주소를 얻어옴
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { 0.f, 2.f, 0.f };
	pVertex[0].dwColor = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);

	pVertex[1].vPosition = { -1.f, -2.f, 1.f };
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPosition = { 1.f, -2.f, 1.f };
	pVertex[2].dwColor = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

	pVertex[3].vPosition = { 1.f, -2.f, -1.f };
	pVertex[3].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	pVertex[4].vPosition = { -1.f, -2.f, -1.f };
	pVertex[4].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

	m_pVB->Unlock();

	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	pIndex[2]._0 = 0;
	pIndex[2]._1 = 3;
	pIndex[2]._2 = 4;

	pIndex[3]._0 = 0;
	pIndex[3]._1 = 4;
	pIndex[3]._2 = 1;

	pIndex[4]._0 = 4;
	pIndex[4]._1 = 3;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 3;
	pIndex[5]._1 = 2;
	pIndex[5]._2 = 1;

	m_pIB->Unlock();

	return S_OK;
}
void CPyramidCol::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CPyramidCol* CPyramidCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPyramidCol* pPyramidCol = new CPyramidCol(pGraphicDev);

	if (FAILED(pPyramidCol->Ready_Buffer()))
	{
		Safe_Release(pPyramidCol);
		MSG_BOX("pPyramidCol Create Failed");
		return nullptr;
	}

	return pPyramidCol;
}
void	CPyramidCol::Free()
{
	CVIBuffer::Free();
}

CComponent* CPyramidCol::Clone(CGameObject* pOwner)
{
	CPyramidCol* pPyramidCol = new CPyramidCol(*this);
	pPyramidCol->SetOwner(pOwner);

	return pPyramidCol;
}
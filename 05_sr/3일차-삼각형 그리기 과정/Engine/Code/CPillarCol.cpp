#include "CPillarCol.h"

CPillarCol::CPillarCol()
{
}

CPillarCol::CPillarCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CPillarCol::CPillarCol(const CPillarCol& rhs)
	:CVIBuffer(rhs)
{
}

CPillarCol::~CPillarCol()
{
}


HRESULT	CPillarCol::Ready_Buffer()
{
	m_dwVtxCnt = 6;
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwTriCnt = 8;
	m_dwFVF = FVF_COL;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;

	VTXCOL* pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 1.f, 0.f };
	pVertex[0].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[1].vPosition = { 0.f, 1.f, sqrtf(3)};
	pVertex[1].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[2].vPosition = { 1.f, 1.f, 0.f };
	pVertex[2].dwColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);

	pVertex[3].vPosition = { -1.f, 0.f, 0.f };
	pVertex[3].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	pVertex[4].vPosition = { 0.f, 0.f, sqrtf(3) };
	pVertex[4].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	pVertex[5].vPosition = { 1.f, 0.f, 0.f };
	pVertex[5].dwColor = D3DXCOLOR(0.f, 0.f, 1.f, 1.f);

	m_pVB->Unlock();

	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 2;
	pIndex[0]._2 = 3;

	pIndex[1]._0 = 3;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 5;

	pIndex[2]._0 = 4;
	pIndex[2]._1 = 1;
	pIndex[2]._2 = 0;

	pIndex[3]._0 = 4;
	pIndex[3]._1 = 0;
	pIndex[3]._2 = 3;

	pIndex[4]._0 = 5;
	pIndex[4]._1 = 2;
	pIndex[4]._2 = 1;

	pIndex[5]._0 = 5;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 4;

	pIndex[6]._0 = 0;
	pIndex[6]._1 = 1;
	pIndex[6]._2 = 2;

	pIndex[7]._0 = 4;
	pIndex[7]._1 = 3;
	pIndex[7]._2 = 5;

	m_pIB->Unlock();
}
void CPillarCol::Render_Buffer()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	CVIBuffer::Render_Buffer();
}

CPillarCol* CPillarCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPillarCol* pPillarCol = new CPillarCol(pGraphicDev);

	if (FAILED(pPillarCol->Ready_Buffer()))
	{
		Safe_Release(pPillarCol);
		MSG_BOX("PillarCol Create Failed");
		return nullptr;
	}
	return pPillarCol;
}

CComponent* CPillarCol::Clone()
{
	return new CPillarCol(*this);
}

void CPillarCol::Free()
{
	CVIBuffer::Free();
}
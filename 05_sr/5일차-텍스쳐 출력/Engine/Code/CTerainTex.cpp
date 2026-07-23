#include "CTerainTex.h"

CTerainTex::CTerainTex()
{
}

CTerainTex::CTerainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CTerainTex::CTerainTex(const CTerainTex& rhs)
	:CVIBuffer(rhs)
{
}

CTerainTex::~CTerainTex()
{
}

HRESULT CTerainTex::Ready_Buffer()
{
	int iXCnt = VTXCNTX;//VTXCNTX
	int iZCnt = VTXCNTZ;//VTXCNTZ

	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = iXCnt * iZCnt * 4;
	m_dwTriCnt = iXCnt * iZCnt * 2;
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;

	VTXTEX* pVertex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	for (int i = 0; i < iZCnt; ++i)
	{
		for (int j = 0; j < iXCnt; ++j)
		{
			pVertex[(i * iXCnt)*4 + j * 4].vPosition = { float(j * VTXITV),0,float((i + 1) * VTXITV) };
			pVertex[(i * iXCnt)*4 + j * 4].vTexUV = { 0.f, 0.f };
	
			pVertex[(i * iXCnt)*4 + j * 4 + 1].vPosition = { float((j + 1) * VTXITV),0, float((i + 1) * VTXITV) };
			pVertex[(i * iXCnt)*4 + j * 4 + 1].vTexUV = { 1.f, 0.f };
	
			pVertex[(i * iXCnt)*4 + j * 4 + 2].vPosition = { (float(j + 1) * VTXITV),0, float(i * VTXITV) };
			pVertex[(i * iXCnt)*4 + j * 4 + 2].vTexUV = { 1.f, 1.f };
	
			pVertex[(i * iXCnt) * 4 + j * 4 + 3].vPosition = { float(j * VTXITV),0, float(i * VTXITV) };
			pVertex[(i * iXCnt) * 4 + j * 4 + 3].vTexUV = { 0.f, 1.f };
		}
	}
	m_pVB->Unlock();
	/////////////////////////////////////////


	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	for (int i = 0; i < iZCnt; ++i)
	{
		for (int j = 0; j < iXCnt; ++j)
		{
			pIndex[(i * iXCnt) * 2 + j * 2]._0 = (i * iXCnt) * 4 + j * 4;
			pIndex[(i * iXCnt) * 2 + j * 2]._1 = (i * iXCnt) * 4 + j * 4 + 1;
			pIndex[(i * iXCnt) * 2 + j * 2]._2 = (i * iXCnt) * 4 + j * 4 + 3;
	
			pIndex[(i * iXCnt) * 2 + j * 2 + 1]._0 = (i * iXCnt) * 4 + j * 4 + 3;
			pIndex[(i * iXCnt) * 2 + j * 2 + 1]._1 = (i * iXCnt) * 4 + j * 4 + 1;
			pIndex[(i * iXCnt) * 2 + j * 2 + 1]._2 = (i * iXCnt) * 4 + j * 4 + 2;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void CTerainTex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CTerainTex* CTerainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerainTex* pTerainTex = new CTerainTex(pGraphicDev);

	if (FAILED(pTerainTex->Ready_Buffer()))
	{
		Safe_Release(pTerainTex);
		MSG_BOX("pTerainTex Create Failed");
		return nullptr;
	}

	return pTerainTex;
}

CComponent* CTerainTex::Clone()
{
	return new CTerainTex(*this);
}

void CTerainTex::Free()
{
	CVIBuffer::Free();
}

#include "CCubeTex.h"

CCubeTex::CCubeTex()
{
}

CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CCubeTex::CCubeTex(const CCubeTex& rhs)
	:CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex()
{
}

HRESULT CCubeTex::Ready_Buffer()
{
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = 24;
	m_dwTriCnt = 12;
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;

	VTXTEX* pVertex = NULL;
	_vec3 pPoint[8];
	pPoint[0] = { -1.f, 1.f, 1.f };
	pPoint[1] = { 1.f, 1.f, 1.f };
	pPoint[2] = { 1.f, 1.f, -1.f };
	pPoint[3] = { -1.f, 1.f, -1.f };
	
	pPoint[4] = { -1.f, -1.f, 1.f };
	pPoint[5] = { 1.f, -1.f, 1.f };
	pPoint[6] = { 1.f, -1.f, -1.f };
	pPoint[7] = { -1.f, -1.f, -1.f };
	// &pVertex : 버텍스 버퍼에 저장된 버텍스 중 첫번째 버텍스의 주소를 얻어옴
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = pPoint[0];
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPosition = pPoint[1];
	pVertex[1].vTexUV = { 1.f, 0.f };

	pVertex[2].vPosition = pPoint[2];
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPosition = pPoint[3];
	pVertex[3].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	pVertex[4].vPosition = pPoint[7];
	pVertex[4].vTexUV = { 0.f,0.f };

	pVertex[5].vPosition = pPoint[6];
	pVertex[5].vTexUV = { 1.f, 0.f };

	pVertex[6].vPosition = pPoint[5];
	pVertex[6].vTexUV = { 1.f, 1.f };

	pVertex[7].vPosition = pPoint[4];
	pVertex[7].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	pVertex[8].vPosition = pPoint[3];
	pVertex[8].vTexUV = { 0.f,0.f };

	pVertex[9].vPosition = pPoint[2];
	pVertex[9].vTexUV = { 1.f, 0.f };

	pVertex[10].vPosition = pPoint[6];
	pVertex[10].vTexUV = { 1.f, 1.f };

	pVertex[11].vPosition = pPoint[7];
	pVertex[11].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	pVertex[12].vPosition = pPoint[2];
	pVertex[12].vTexUV = { 0.f,0.f };

	pVertex[13].vPosition = pPoint[1];
	pVertex[13].vTexUV = { 1.f, 0.f };

	pVertex[14].vPosition = pPoint[5];
	pVertex[14].vTexUV = { 1.f, 1.f };

	pVertex[15].vPosition = pPoint[6];
	pVertex[15].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	pVertex[16].vPosition = pPoint[1];
	pVertex[16].vTexUV = { 0.f,0.f };

	pVertex[17].vPosition = pPoint[0];
	pVertex[17].vTexUV = { 1.f, 0.f };

	pVertex[18].vPosition = pPoint[4];
	pVertex[18].vTexUV = { 1.f, 1.f };

	pVertex[19].vPosition = pPoint[5];
	pVertex[19].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	pVertex[20].vPosition = pPoint[0];
	pVertex[20].vTexUV = { 0.f,0.f };

	pVertex[21].vPosition = pPoint[3];
	pVertex[21].vTexUV = { 1.f, 0.f };

	pVertex[22].vPosition = pPoint[7];
	pVertex[22].vTexUV = { 1.f, 1.f };

	pVertex[23].vPosition = pPoint[4];
	pVertex[23].vTexUV = { 0.f, 1.f };
	/////////////////////////////////////////

	m_pVB->Unlock();

	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;
	
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	pIndex[2]._0 = 5;
	pIndex[2]._1 = 6;
	pIndex[2]._2 = 4;
	
	pIndex[3]._0 = 4;
	pIndex[3]._1 = 6;
	pIndex[3]._2 = 7;
	
	pIndex[4]._0 = 3;
	pIndex[4]._1 = 2;
	pIndex[4]._2 = 5;
	
	pIndex[5]._0 = 3;
	pIndex[5]._1 = 5;
	pIndex[5]._2 = 4;
	//
	pIndex[6]._0 = 12;
	pIndex[6]._1 = 13;
	pIndex[6]._2 = 14;
	
	pIndex[7]._0 = 12;
	pIndex[7]._1 = 14;
	pIndex[7]._2 = 15;
	//
	pIndex[8]._0 = 16;
	pIndex[8]._1 = 17;
	pIndex[8]._2 = 18;
	
	pIndex[9]._0 = 16;
	pIndex[9]._1 = 18;
	pIndex[9]._2 = 19;
	//
	pIndex[10]._0 = 20;
	pIndex[10]._1 = 21;
	pIndex[10]._2 = 22;
	
	pIndex[11]._0 = 20;
	pIndex[11]._1 = 22;
	pIndex[11]._2 = 23;
	m_pIB->Unlock();

	return S_OK;
}

void CCubeTex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CCubeTex* CCubeTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeTex* pCubeTex = new CCubeTex(pGraphicDev);

	if (FAILED(pCubeTex->Ready_Buffer()))
	{
		Safe_Release(pCubeTex);
		MSG_BOX("pCubeTex Create Failed");
		return nullptr;
	}

	return pCubeTex;
}

CComponent* CCubeTex::Clone()
{
	return new CCubeTex(*this);
}

void CCubeTex::Free()
{
	CVIBuffer::Free();
}

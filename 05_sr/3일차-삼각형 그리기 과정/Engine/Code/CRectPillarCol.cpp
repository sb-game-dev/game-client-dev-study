
#include "CVIBuffer.h"
#include "CRectPillarCol.h"

CRectPillarCol::CRectPillarCol()
{
}

CRectPillarCol::CRectPillarCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CRectPillarCol::CRectPillarCol(const CRectPillarCol& rhs)
	:CVIBuffer(rhs.m_pGraphicDev)
{
}

CRectPillarCol::~CRectPillarCol()
{
}

#pragma once
#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer :  public CComponent
{
protected:
	explicit CVIBuffer();
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer();

public:
	virtual	HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

protected:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;

	_ulong			m_dwVtxSize;	// 버텍스의 크기
	_ulong			m_dwVtxCnt;		// 버텍스의 개수
	_ulong			m_dwTriCnt;		// 삼각형 개수
	_ulong			m_dwFVF;		// FVF 속성 값

	LPDIRECT3DINDEXBUFFER9			m_pIB;

	_ulong			m_dwIdxSize;	// 인덱스의 크기
	D3DFORMAT		m_IdxFmt;		// 인덱서의 형식

public:
	virtual void Free();

};

END

#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

//#include "d3dUtility.h"
#include <string>
#include <vector>

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
protected:
	explicit CTerrainTex();
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTex(const CTerrainTex& rhs);
	virtual ~CTerrainTex();

public:
	virtual HRESULT		Ready_Buffer();							// 가로 버텍스 길이, 세로 버텍스 길이, 버텍스 간격 추가
	virtual void		Render_Buffer();

public:
	static CTerrainTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);	// 가로 버텍스 길이, 세로 버텍스 길이, 버텍스 간격 추가

    bool	Ready_HeightMap(const wstring& pFilePath);

	void	SetHeightmapEntry(int row, int col, int value);
	float	GetHeight(float fX, float fZ);
	float	GetHeight_UsePlane(float fX, float fZ);

	vector<_vec3> GetVertex()	{ return m_vVertex; }
	vector<_vec3> GetIndex()	{ return m_vIndex; }

	virtual CComponent* Clone(CGameObject* pOwner) override;

private:
	virtual void	Free();

	int		GetHeightmapEntry(int iRow, int iCol);

	float Lerp(float a, float b, float t) { return a - (a * t) + (b * t); }


private:
	vector<int>			m_vHeightmap;
	vector<_vec3>		m_vVertex;
	vector<_vec3>		m_vIndex;
	float				m_fHeightWeight;

	// CVIBuffer을(를) 통해 상속됨
};

END



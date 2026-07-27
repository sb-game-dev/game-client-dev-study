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
	bool		ReadBmp(const char* filename);

    bool Ready_HeightMap(const wstring& pFilePath);

	int  GetHeightmapEntry(int row, int col);
	void SetHeightmapEntry(int row, int col, int value);

	virtual CComponent* Clone();

private:
	virtual void	Free();

private:
	std::vector<int>	m_vHeightmap;
	float				m_fHeightWeight;
};

END



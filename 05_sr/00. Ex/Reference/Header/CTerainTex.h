#pragma once
#include "CVIBuffer.h"
#include "Engine_Define.h"

//#include "d3dUtility.h"
#include <string>
#include <vector>

BEGIN(Engine)

class ENGINE_DLL CTerainTex : public CVIBuffer
{
protected:
	explicit CTerainTex();
	explicit CTerainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerainTex(const CTerainTex& rhs);
	virtual ~CTerainTex();

public:
	virtual HRESULT		Ready_Buffer();
	virtual void		Render_Buffer();

public:
	static CTerainTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
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



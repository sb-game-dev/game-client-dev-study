#include "CTerrainTex.h"
#include <fstream>
#include <cmath>
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

CTerrainTex::CTerrainTex()
{
}

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev), m_fHeightWeight(1.f)
{
}

CTerrainTex::CTerrainTex(const CTerrainTex& rhs)
	:CVIBuffer(rhs)
{
}

CTerrainTex::~CTerrainTex()
{
}

HRESULT CTerrainTex::Ready_Buffer()
{
	int iXCnt = VTXCNTX;//
	int iZCnt = VTXCNTZ;//

	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = iXCnt * iZCnt ;
	m_dwTriCnt = (iXCnt-1) * (iZCnt-1) * 2; // (iXCnt-1) * (iZCnt - 1) * 2
	m_dwFVF = FVF_TEX;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;

	VTXTEX* pVertex = NULL;
	int i = 0;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	float uCoordIncrementSize = 1.f / (iXCnt-1); // 1.f / (iXCnt - 1)
	float vCoordIncrementSize = 1.f / (iZCnt-1); // 1.f / (iZCnt - 1)
	m_fHeightWeight = 0.05f;

	for (int z = 0; z > -iZCnt; z-=VTXITV)
	{
		int j = 0;
		for (int x = 0; x < iXCnt; x+=VTXITV)
		{
			//pVertex[(z * iXCnt) * 4 + x * 4].vPosition = { float(x * VTXITV),0,float((z + 1) * VTXITV) };
			//pVertex[(z * iXCnt) * 4 + x * 4].vTexUV = { 0.f, 0.f };
			//
			//pVertex[(z * iXCnt) * 4 + x * 4 + 1].vPosition = { float((x + 1) * VTXITV),0, float((z + 1) * VTXITV) };
			//pVertex[(z * iXCnt) * 4 + x * 4 + 1].vTexUV = { 1.f, 0.f };
			//
			//pVertex[(z * iXCnt) * 4 + x * 4 + 2].vPosition = { (float(x + 1) * VTXITV),0, float(z * VTXITV) };
			//pVertex[(z * iXCnt) * 4 + x * 4 + 2].vTexUV = { 1.f, 1.f };
			//
			//pVertex[(z * iXCnt) * 4 + x * 4 + 3].vPosition = { float(x * VTXITV),0, float(z * VTXITV) };
			//pVertex[(z * iXCnt) * 4 + x * 4 + 3].vTexUV = { 0.f, 1.f };
			///////////////////////////////////////////////////////

			int iIndex = i * iXCnt + j;
			pVertex[iIndex].vPosition = { float(x),0,float(z)};
			pVertex[iIndex].vTexUV = { j * uCoordIncrementSize, i * vCoordIncrementSize };
			++j;
		}
		++i;
	}
	m_pVB->Unlock();
	/////////////////////////////////////////


	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	int iBaseIndex = 0;
	for (int i = 0; i < iZCnt-1; ++i)
	{
		for (int j = 0; j < iXCnt-1; ++j)
		{
			//pIndex[(i * iXCnt) * 2 + j * 2]._0 = (i * iXCnt) * 4 + j * 4;
			//pIndex[(i * iXCnt) * 2 + j * 2]._1 = (i * iXCnt) * 4 + j * 4 + 1;
			//pIndex[(i * iXCnt) * 2 + j * 2]._2 = (i * iXCnt) * 4 + j * 4 + 3;
			//
			//pIndex[(i * iXCnt) * 2 + j * 2 + 1]._0 = (i * iXCnt) * 4 + j * 4 + 3;
			//pIndex[(i * iXCnt) * 2 + j * 2 + 1]._1 = (i * iXCnt) * 4 + j * 4 + 1;
			//pIndex[(i * iXCnt) * 2 + j * 2 + 1]._2 = (i * iXCnt) * 4 + j * 4 + 2;
			////////////////////////////////////////////////////////////////////////

			pIndex[iBaseIndex]._0 = i * iXCnt + j;
			pIndex[iBaseIndex]._1 = i * iXCnt + j + 1;
			pIndex[iBaseIndex]._2 = (i + 1) * iXCnt + j;

			pIndex[iBaseIndex + 1]._0 = (i + 1) * iXCnt + j;
			pIndex[iBaseIndex + 1]._1 = i * iXCnt + j + 1;
			pIndex[iBaseIndex + 1]._2 = (i + 1) * iXCnt + j + 1;

			iBaseIndex += 2;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void CTerrainTex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CTerrainTex* CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainTex* pTerrainTex = new CTerrainTex(pGraphicDev);

	if (FAILED(pTerrainTex->Ready_Buffer()))
	{
		Safe_Release(pTerrainTex);
		MSG_BOX("pTerrainTex Create Failed");
		return nullptr;
	}

	return pTerrainTex;
}

int CTerrainTex::GetHeightmapEntry(int iRow, int iCol)
{
	return m_vHeightmap[iRow * VTXCNTX + iCol];
}

float CTerrainTex::GetHeight(float fX, float fZ)
{
	fZ *= -1;

	float fCol = ::floorf(fX);
	float fRow = ::floorf(fZ);

	float fA = GetHeightmapEntry(fRow, fCol);
	float fB = GetHeightmapEntry(fRow, fCol + 1);
	float fC = GetHeightmapEntry(fRow + 1, fCol);
	float fD = GetHeightmapEntry(fRow + 1, fCol + 1);


	float fDx = fX - fCol;
	float fDz = fZ - fRow;

	float fHeight = 0.0f;
	if (fDz < 1.0f - fDx)  
	{
		float uy = fB - fA; 
		float vy = fC - fA; 

		fHeight = fA + Lerp(0.0f, uy, fDx) + Lerp(0.0f, vy, fDz);
	}
	else 
	{
		float uy = fC - fD; 
		float vy = fB - fD; 

		fHeight = fD + Lerp(0.0f, uy, 1.0f - fDx) + Lerp(0.0f, vy, 1.0f - fDz);
	}

	return fHeight;
}

void CTerrainTex::SetHeightmapEntry(int row, int col, int value)
{
	m_vHeightmap[row * VTXCNTX + col] = value;
}

CComponent* CTerrainTex::Clone()
{
	return new CTerrainTex(*this);
}

bool CTerrainTex::ReadBmp(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file) return false;

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

	if (fileHeader.bfType != 0x4D42 || infoHeader.biBitCount != 32) {
		return false;
	}

	std::vector<BYTE> in(m_dwVtxCnt * 4);

	file.seekg(fileHeader.bfOffBits, std::ios::beg);
	file.read((char*)&in[0], // buffer
		in.size());// number of bytes to read into buffer

	m_vHeightmap.resize(m_dwVtxCnt * 4);

	for (int i = 0; i < in.size(); i++)
		m_vHeightmap[i] = in[i];
	file.close();

	return true;
}


void CTerrainTex::Free()
{
	CVIBuffer::Free();
}


bool CTerrainTex::Ready_HeightMap(const wstring& pFilePath)
{
	ifstream inFile(pFilePath.c_str(), ios::binary);
	if (!inFile)
		return false;

	BITMAPFILEHEADER fileHeader = {};
	BITMAPINFOHEADER infoHeader = {};

	inFile.read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
	inFile.read((char*)&infoHeader, sizeof(BITMAPINFOHEADER));

	if (!inFile || fileHeader.bfType != 0x4D42) {
		inFile.close();
		return false;
	}

	int width = infoHeader.biWidth;
	int height = abs(infoHeader.biHeight); // 음수면 top-down 저장
	bool topDown = infoHeader.biHeight < 0;
	int bitCount = infoHeader.biBitCount;    // 이 파일은 32

	if (bitCount != 8 && bitCount != 24 && bitCount != 32) {
		inFile.close();
		return false;
	}

	int bytesPerPixel = bitCount / 8;
	int rowSize = ((width * bitCount + 31) / 32) * 4; // 4바이트 정렬된 실제 행 크기

	inFile.seekg(fileHeader.bfOffBits, ios::beg); // 팔레트 포함 헤더 전부 건너뛰기

	vector<BYTE> vRow(rowSize);
	vector<vector<BYTE>> vRows(height);

	for (int y = 0; y < height; ++y) {
		inFile.read((char*)&vRow[0], rowSize);
		if (!inFile) {
			inFile.close();
			return false;
		}
		vRows[y].assign(vRow.begin(), vRow.end());
	}
	inFile.close();

	vector<BYTE> vIn;
	vIn.reserve(m_dwVtxCnt);

	// BMP는 기본적으로 bottom-up이므로, top-down이 아니면 순서를 뒤집어서 위->아래로 재정렬
	auto extractGray = [&](const vector<BYTE>& row)
		{
			for (int x = 0; x < width; ++x) {
				const BYTE* px = &row[x * bytesPerPixel];
				// 8bpp면 px[0]이 팔레트 인덱스(그레이스케일 팔레트 가정),
				// 24/32bpp면 B=G=R이므로 아무 채널이나 사용 (여기선 B채널)
				vIn.push_back(px[0]);
			}
		};

	if (topDown) {
		for (int y = 0; y < height; ++y) {
			extractGray(vRows[y]);
		}
	}
	else {
		for (int y = height - 1; y >= 0; --y) {
			extractGray(vRows[y]);
		}
	}
	vIn.resize(m_dwVtxCnt);

	m_vHeightmap.clear();
	m_vHeightmap.resize(m_dwVtxCnt);
	for (DWORD i = 0; i < m_dwVtxCnt; ++i) {
		m_vHeightmap[i] = vIn[i];
	}


	// Vertex 높이값 재설정
	VTXTEX* pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (int i = 0; i < vIn.size(); ++i) {
		m_vHeightmap[i] *= 0.3f;
		pVertex[i].vPosition.y = m_vHeightmap[i];
	}

	m_pVB->Unlock();

	return true;
}

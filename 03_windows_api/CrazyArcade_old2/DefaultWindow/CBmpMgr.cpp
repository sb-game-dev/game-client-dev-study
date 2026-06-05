#include "pch.h"
#include "CBmpMgr.h"
#include "CMyBmp.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	// 못찾으면 m_mapBit.end() 반환하는데 이때 못찾았다는것은 새로 등록할 수 있다는 것.
	// 즉 추가하고 싶은 이미지가 있는데 그 이미지가 이미 있다면 추가하지 못하게 막는 장치
	if (iter == m_mapBit.end())
	{
		CMyBmp* pMyBmp = new CMyBmp;

		pMyBmp->LoadBmp(pFilePath);

		m_mapBit.insert({ pImgKey, pMyBmp });
	}
}

HDC CBmpMgr::FindImage(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->GetMemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), tagDeleteMap());
	m_mapBit.clear();
}

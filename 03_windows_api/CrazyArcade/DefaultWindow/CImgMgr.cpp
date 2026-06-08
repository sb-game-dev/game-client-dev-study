#include "pch.h"
#include "CImgMgr.h"
CImgMgr* CImgMgr::m_pInstance = nullptr;

CImgMgr::CImgMgr()
{
}

CImgMgr::~CImgMgr()
{
}

void CImgMgr::InsertImg(const WCHAR* pFilePath, const WCHAR* pImgKey)
{
    auto iter = find_if(m_ImgMap.begin(), m_ImgMap.end(), tagFinder(pImgKey));

    if (iter == m_ImgMap.end()) {
        Image* pImg = Image::FromFile(pFilePath);
        m_ImgMap.insert({ pImgKey, pImg });
    }
}

Image* CImgMgr::FindImg(const WCHAR* pImgKey)
{
    auto iter = find_if(m_ImgMap.begin(), m_ImgMap.end(), tagFinder(pImgKey));

    if (iter == m_ImgMap.end())
        return nullptr;

    return iter->second;
}

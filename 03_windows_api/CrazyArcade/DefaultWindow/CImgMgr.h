#pragma once
#include "Define.h"
class CImgMgr
{
public:
	CImgMgr();
	CImgMgr(const CImgMgr* rhs) = delete;
	CImgMgr& operator=(const CImgMgr* rhs) = delete;
	~CImgMgr();

public:
	void InsertImg(const WCHAR* pFilePath, const WCHAR* pImgKey);
	Image* FindImg(const WCHAR* pImgKey);

public:
	static CImgMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CImgMgr;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CImgMgr* m_pInstance;
	map<const WCHAR*, Image*> m_ImgMap;
};


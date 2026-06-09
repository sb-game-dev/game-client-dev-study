#pragma once
#include "CMyBmp.h"
class CBmpMgr
{
private:
	CBmpMgr();
	CBmpMgr(const CBmpMgr& rhs) = delete;
	CBmpMgr& operator = (CBmpMgr& rCBmpMgr) = delete;
	~CBmpMgr();
public:
	void	InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC		FindImage(const TCHAR* pImgKey);

	void	Release();

public:
	static CBmpMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;
		return m_pInstance;
	}

	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CMyBmp* >		m_mapBit;
};


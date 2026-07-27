#include "CKeyMgr.h"
#include <io.h>
#include <iostream>

IMPLEMENT_SINGLETON(CKeyMgr)
CKeyMgr::CKeyMgr()
{
	ZeroMemory(&m_bCurState, sizeof(m_bCurState));
	ZeroMemory(&m_bPreState, sizeof(m_bPreState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::KeyPressing(int iKey)
{
	return m_bCurState[iKey];
}

bool CKeyMgr::KeyUp(int iKey)
{
	return m_bPreState[iKey] && !m_bCurState[iKey];
}

bool CKeyMgr::KeyDown(int iKey)
{
	return !m_bPreState[iKey] && m_bCurState[iKey];
}

void CKeyMgr::KeyUpdate()
{
	for (int i = 0; i < 0xff; ++i)
	{
		m_bPreState[i] = m_bCurState[i];
		m_bCurState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

#include "CObj.h"
#include "pch.h"
CObj::CObj()
{
	//strcpy_s(m_szName, sizeof(m_szName), szName);
	//m_iHp = iHp;
	//m_iAttack = iAttack;
}

CObj::~CObj()
{

}


void CObj::Initialize()
{

}
void CObj::Update()
{
	
}
void CObj::Release()
{

}
CObj* CObj::Create()
{
	CObj* pObj = new CObj();
	return pObj;
}
void CObj::Destroy()
{
	delete this;
}
void CObj::Render()
{
	cout << "===================================" << endl;
	cout << "이름: " << m_szName << endl;
	cout << "체력: " << (m_iHp >= 0 ? m_iHp : 0) << "\t" << "공력력: " << m_iAttack << endl;
}
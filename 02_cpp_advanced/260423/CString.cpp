#include "CString.h"

CString::CString()
{
	szName = nullptr;
}

CString::CString(const char* temp)
{
	const int len = strlen(temp);
	szName = new char[len+1];
	strcpy_s(szName, len+1, temp);
}

CString::CString(const CString& Tmp)
{
	const int len = strlen(Tmp.szName);
	szName = new char[len + 1];
	strcpy_s(szName, len + 1, Tmp.szName);
}

CString::~CString()
{
	delete[] szName;
	szName = nullptr;
}

CString& CString::operator=(CString& Tmp)
{
	const int len = strlen(Tmp.szName);
	szName = new char[len + 1];
	strcpy_s(szName, len + 1, Tmp.szName);
	return (*this);

}
CString& CString::operator=(const char* temp)
{
	const int len = strlen(temp);
	szName = new char[len + 1];
	strcpy_s(szName, len + 1, temp);
	return (*this);
}

CString CString::operator+(CString& Tmp)
{
	CString Result;
	const int len = strlen(Tmp.szName) + strlen(szName);
	Result.szName = new char[len+1];
	for (int i=0; i < strlen(szName); i++)
	{
		Result.szName[i] = szName[i];
	}
	
	for (int i = 0; i < strlen(Tmp.szName); i++)
	{
		Result.szName[i+ strlen(szName)] = Tmp.szName[i];
	}
	Result.szName[len] = NULL;
	return Result;
}

CString CString::operator+(const char* temp)
{
	CString Result;
	const int len = strlen(temp) + strlen(szName);
	Result.szName = new char[len + 1];
	for (int i = 0; i < strlen(szName); i++)
	{
		Result.szName[i] = szName[i];
	}

	for (int i = 0; i < strlen(temp); i++)
	{
		Result.szName[i + strlen(szName)] = temp[i];
	}
	Result.szName[len] = NULL;
	return Result;
}

bool CString::operator==(const char* temp)
{
	if (strcmp(temp, szName)) return false;
	return true;
}

bool CString::operator==(CString& Tmp)
{
	if (strcmp(Tmp.szName, szName)) return false;
	return true;
}


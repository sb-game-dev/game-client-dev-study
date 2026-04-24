#include "pch.h"
#include "CString.h"
CString operator+(const char* temp, CString& Tmp)
{
	CString Result;
	const int len = strlen(temp) + strlen(Tmp.szName);
	Result.szName = new char[len + 1];
	for (int i = 0; i < strlen(temp); i++)
	{
		Result.szName[i + strlen(Tmp.szName)] = temp[i];
	}
	for (int i = 0; i < strlen(Tmp.szName); i++)
	{
		Result.szName[i] = Tmp.szName[i];
	}
	Result.szName[len] = NULL;
	return Result;
}
int main()
{
	//CString s = "Test";
	CString t = "Helloasdfasfdasfdasfasdfasfd";
	CString s = "Worldasdfasfasfafdfasfdasfdasdf";

	//cout << t.szName << endl;
	//
	//cout << s.szName << endl;
	CString r = "World" + t;

	cout << r.szName << endl;

	//s = "Test";
	//CString r = "Hello" + "World";
	//cout << r.szName << endl;
	//if (s == "Testzz")
	//{
	//	cout << "일치합니다" << endl;
	//}
	//else
	//{
	//	cout << "일치하지 않습니다" << endl;
	//}

	
}
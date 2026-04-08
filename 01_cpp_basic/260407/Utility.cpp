#include "pch.h"
#include "Utility.h"

void setColor(unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}
char* IntToString(int iNum)
{
	
	char* res = new char[32];
	if (iNum == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return res;
	}
	int iTemp = iNum;
	int iSize = 0;
	while (iTemp)
	{
		iSize++;
		iTemp /= 10;
	}

	res[iSize] = '\0';
	while (iNum)
	{
		res[--iSize] = iNum % 10 + '0';
		iNum /= 10;
	}
	return res;
}

void PrintSysMessage(const char szName[])
{
	cout << szName << endl;
	system("pause");
}
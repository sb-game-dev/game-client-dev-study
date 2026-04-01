#include<iostream>
using namespace std;
int StringLength(char string[]);
void StringReverse(char string[]);
int main()
{
	//char cString[64] = "";
	//cin >> cString;
	//cout << "입력한 문자열 " << cString << "의 길이는 " << StringLength(cString) << "입니다." << endl;
	//
	//StringReverse(cString);
	const char* pName = "helloworldSDdADAsdasaASDFSAFSADFSADFdfasdfwafeacdfasdfsa";
	//cin >> pName;
	cout << pName << endl;
}
int StringLength(char string[])
{
	int iCnt = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		iCnt++;
	}
	return iCnt;
	
}
void StringReverse(char string[])
{
	for (int i = StringLength(string) - 1; i >= 0; i--)
	{
		cout << string[i];
	}
	cout << endl;
}
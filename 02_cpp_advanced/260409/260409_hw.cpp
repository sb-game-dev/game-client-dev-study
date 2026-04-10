#include "CStudent.h"
#define SAFE_ARR_DELET(p) {delete[] p;p = nullptr;}
void AddStudent(CStudent** ppStudent, int iOrigSize, int NewSize);
void PrintStudent(CStudent* pStudent, int start, int iCnt);
void FindStudent(CStudent* pStudent, int iCnt, char* );
void StudentCopy(CStudent** From, CStudent** To, int iCnt);
int main()
{
	// 동적 배열을 이용한 성적표 만들기
	// - 동적 배열(학생)과 클래스를 이용하여 제작하라
	// 1. 추가 2. 출력 3. 검색 4. 종료
	int iInput,iCnt;
	char tempName[32];

	cout << "학생 수를 입력하세요:";
	cin >> iCnt;

	CStudent* Stu = new CStudent[100];
	AddStudent(&Stu, 0, iCnt);
	PrintStudent(Stu, 0, iCnt);
	system("pause");
	while (true)
	{
		system("cls");
		cout << "1. 추가 2. 출력 3. 검색 4. 종료: ";
		cin >> iInput;
		switch (iInput)
		{
		case 1:
			AddStudent(&Stu, iCnt, iCnt + 1);
			++iCnt;
			break;
		case 2:
			PrintStudent(Stu, 0, iCnt);
			break;
		case 3:
			cout << "검색할 학생의 이름을 알려주세요: ";
			cin >> tempName;
			FindStudent(Stu, iCnt,tempName);
			break;
		case 4:
			return 0;
		default:
			cout << "잘못된 입력입니다. 다시 입력해주세요" << endl;
		}
		system("pause");
	}
	SAFE_ARR_DELET(Stu);
}


void AddStudent(CStudent** Temp, int iOrigSize, int NewSize)
{
	int iInput;
	char tempName[32];
	//CStudent* Temp = new CStudent[NewSize];
	//
	//StudentCopy(ppStudent, &Temp, iOrigSize);

	for (int i = iOrigSize; i < NewSize; i++)
	{
		cout << "학생 이름을 입력하세요: ";
		cin >> tempName;

		(*Temp)[i].SetszName(tempName);
		cout << "국어: ";
		cin >> iInput;
		(*Temp)[i].SetiKor(iInput);
		cout << "수학: ";
		cin >> iInput;
		(*Temp)[i].SetiMath(iInput);
		cout << "영어: ";
		cin >> iInput;
		(*Temp)[i].SetiEng(iInput);
		(*Temp)[i].Sum();
		(*Temp)[i].Aver();
	}
	//SAFE_ARR_DELET(*ppStudent);
	//
	//*ppStudent = new CStudent[NewSize];

	//StudentCopy(&Temp, ppStudent, NewSize);
	//
	//SAFE_ARR_DELET(Temp);
}

void PrintStudent(CStudent* pStudent, int start,int iCnt)
{
	for (int i = start; i < iCnt; i++)
	{
		cout << "========================================\n";
		cout << i + 1 << "번 학생\t";
		cout << "이름: ";
		cout << pStudent[i].GetszName();
		cout << "\n국어: ";
		cout << pStudent[i].GetiKor();
		cout << "\n수학: ";
		cout << pStudent[i].GetiMath();
		cout << "\n영어: ";
		cout << pStudent[i].GetiEng();
		cout << "\n총합: ";
		cout << pStudent[i].GetiSum();
		cout << "\n평균: ";
		cout << pStudent[i].GetfAver() << endl;
	}
}

void FindStudent(CStudent* pStudent, int iCnt, char* tempName)
{
	for (int i = 0; i < iCnt; i++)
	{
		if (strcmp(pStudent[i].GetszName(), tempName)==0)
		{
			PrintStudent(pStudent, i, i + 1);
			return;
		}
	}
	cout << "찾는 학생이 없습니다." << endl;
}

void StudentCopy(CStudent** From, CStudent** To, int iCnt)
{
	for (int i = 0; i < iCnt; i++)
	{
		(*To)[i].SetszName((*From[i]).GetszName());

		(*To)[i].SetiKor((*From[i]).GetiKor());
		
		(*To)[i].SetiMath((*From[i]).GetiMath());
		
		(*To)[i].SetiEng((*From[i]).GetiEng());
		
		(*To)[i].SetiSum((*From[i]).GetiSum());
		
		(*To)[i].SetfAver((*From[i]).GetfAver());
	}
}
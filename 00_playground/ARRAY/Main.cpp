#include "pch.h"
#include <array>
class CObj
{
public:
	CObj(int iNum):iAttack(iNum) {}
	~CObj() {}

public:
	int iAttack;
};
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	array<CObj*, 10>arr ;

	
	for (array<CObj*, 10>::iterator it = arr.begin();
		it != arr.end();
		++it)
	{
		*it = new CObj(rand() % 10);
	}

	for (array<CObj*, 10>::iterator it = arr.begin();
		it != arr.end();
		++it)
	{
		cout << (*it)->iAttack << endl;
	}


	return 0;
}
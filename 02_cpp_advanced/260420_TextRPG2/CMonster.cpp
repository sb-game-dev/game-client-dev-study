#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const char* szName, int iHp, int iAttack)
	: CObj(szName,iHp,iAttack)
{

}

CMonster::~CMonster()
{
}

#pragma once
#include "pch.h"
#define SAFE_DELETE(p) if(p){delete p; p = nullptr;}
// 메모리 누수 확인
//-----헤더-----
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

struct Info
{
	char szName[32];
	int iHp, iAttack;
};
#pragma once
#include <iostream>
#include <ctime>

using namespace std;
#define SAFE_DELETE(p) {delete p;p = nullptr;}
#define SAFE_ARR_DELETE(p) {delete[] p;p = nullptr;}


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif


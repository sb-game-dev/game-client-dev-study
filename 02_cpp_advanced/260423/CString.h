#pragma once
#include "pch.h"
class CString
{
public:
	CString();
	CString(const char* temp);
	CString(const CString& Tmp);
	~CString();
public:

	CString& operator= (CString& Tmp);
	CString& operator= (const char*);

	CString operator+(CString& Tmp);
	CString operator+(const char*);

	bool operator==(const char*);
	bool operator== (CString& Tmp);

	//char* operator<<();
public:
	char* szName;
};


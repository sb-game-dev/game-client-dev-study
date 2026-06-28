#pragma once
#include "Define.h"
class CLine
{
public:
	CLine();
	CLine(const LINEPOINT& tLeft, const LINEPOINT& tRight);
	~CLine();

public:
	const LINE& GetLine() { return m_tLine; }

	void Render(HDC hDC);
private:
	LINE m_tLine;
};


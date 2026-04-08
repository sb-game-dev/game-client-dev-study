#pragma once

enum item
{
	Normal = 1,
	Magic,
	Rare,
	Legendary,
	Unique,
	END
};

extern const int iItemColor[];
extern const char* szItemRarity[];
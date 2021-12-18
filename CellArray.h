#pragma once
#include "Cell.h"

class CellArray : public Cell
{
public:
	Cell cellMatrix[CELL_COUNT][CELL_COUNT];
public:
	CellArray();
	Cell GetCellByIndex(int x, int y);
	void SetCellByIndex(int x, int y, string value);
	void ShowBattleField();
	void CreateBattleField();
	~CellArray();
};


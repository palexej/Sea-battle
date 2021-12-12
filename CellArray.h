#pragma once
#include "Cell.h"

class CellArray : public Cell
{
private:
	Cell cellMatrix[CELL_COUNT][CELL_COUNT];
public:
	CellArray();
	void ShowBattleField();
	void CreateBattleField();
	~CellArray();
};


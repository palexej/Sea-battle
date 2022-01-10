#include "pch.h"
#include "CellArray.h"

#include <iostream>
#include  <locale.h>
CellArray::CellArray()
{
	
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			cellMatrix[i][j] = new Cell(i, j, EMPTY,-1);
		}
	}
	CreateBattleField();
}
Cell CellArray::GetCellByIndex(int x, int y)
{
	return  cellMatrix[x][y];
}
void CellArray::SetCellByIndex(int x, int y,string value)
{
	cellMatrix[x][y].setCellType(value);
}

void CellArray::ShowBattleField()
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			cout << GetCellByIndex(i,j).getCellType();
		}
		cout << "\n";
	}
}
void CellArray::CreateBattleField()
{
	setlocale(LC_ALL, "Russian");
	const int LETTERS_COUNT = 11;
	const int NUMBERS_COUNT = 11;

	string letterArray = " ÀÁÂÃÄÅÆÇÈÊ";
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			if (i == 0 && j < LETTERS_COUNT)
			{
				string str;
				str = letterArray[j];
				cellMatrix[i][j].setCellType(str);
				continue;
			}

			if (j == 0 && i < NUMBERS_COUNT)
			{
				cellMatrix[i][j].setCellType(std::to_string(i));//ïðåîáðàçîâàíèå èíòà â áóêâó
				continue;
			}


			if (i > 10 || j > 10)
			{
				cellMatrix[i][j].setCellType(BORDERS);
			}
		}
	
	}
}

CellArray::~CellArray()
{
}

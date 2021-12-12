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
			Cell* cell = new Cell(i, j,EMPTY);
			cellMatrix[i][j] = new Cell(*cell);
		}
	}
	CreateBattleField();
}

void CellArray::ShowBattleField()
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			cout << cellMatrix[i][j].getCellType();
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

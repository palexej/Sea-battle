// Морской бой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Cell.h"
#include "CellArray.h"
#include <string.h>
using namespace std;


int main()
{
	CellArray* playerField = new CellArray;
	playerField->ShowBattleField();
	system("pause");
	return 0;

}

// Морской бой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <map>

#include "Cell.h"
#include "CellArray.h"
#include  "Ship.h"
#include <string.h>
using namespace std;

map<int, int> shipDictionary={
	{
		1,0
	},
	{
		2,0
	},
	{
		3,0
	},
	{
		4,0
	},
};

int main()
{
	CellArray playerField;

	Cell cell;

	int x = 0,  y = 0, verticalNumber,lenghtValue;
	bool verticalValue;
	int shipCount=0;
	while (shipCount < 5)
	{
		playerField.ShowBattleField();

		cout << "Введите координату по оси Х и У: " << endl;
		cin >> x >> y;

		cout << "Введите, как разместить корабль(0 - вертикально, любое число - горизонтально)" << endl;
		cin >> verticalNumber;
		if (verticalNumber == 0)
		{
			verticalValue = true;
		}
		else
		{
			verticalValue = false;
		}
		cout << "Введите длину корабля от 1 до 4" << endl;
		cin >> lenghtValue;
		Ship ship(x, y, verticalValue, lenghtValue);

		if (ship.AddShip(playerField))
		{
			cout << "Корабль размещен" << endl;
			shipCount++;
		}
		else
		{
			cout << "Невозможно размещение в этой позиции" << endl;
		}
	}

	system("pause");
	return 0;

}

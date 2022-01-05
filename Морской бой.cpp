// Морской бой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <map>
#include <random>

#include "Cell.h"
#include "CellArray.h"
#include  "Ship.h"
#include <string.h>
using namespace std;
vector<Ship> player_vector;
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
 bool CheckShipCount(map<int, int> &shipDictionary)
{
	if (shipDictionary[2] > 4 || shipDictionary[3] > 2 || shipDictionary[4]>1)
	{
		return false;
	}

	return true;
}
void RandomShipPositions(map<int, int> &shipDictionary, CellArray& cellsArray,vector<Ship> &ships)
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом
	

	int startShipLenght = 1;

 	while( shipDictionary[4]<1)//пока не добавлен корабль длины 4
	{
		if (shipDictionary[1] == 4)
		{
			startShipLenght = 2;
		}
		if (shipDictionary[2] == 3)
		{
			startShipLenght = 3;
		}

		if (shipDictionary[3]==2)
		{
			startShipLenght = 4;
		}
		uniform_int_distribution<int> randomShipLenght(1, 10);//генерация чисел в указанном интервале
		int randomX = randomShipLenght(rd);
		int randomY = randomShipLenght(rd);

		uniform_int_distribution<int> randomVerticalOrientation(0, 1);//генерация чисел в указанном интервале

		int randomIntegerVal = randomVerticalOrientation(rd);
		bool randomVertical;
		if (randomIntegerVal == 1)
		{
			randomVertical = true;
		}
		else
		{
			randomVertical = false;
		}

		int randomLenght = startShipLenght;

		

		Ship ship(randomX, randomY, randomVertical, randomLenght,1);
		if (cellsArray.GetCellByIndex(randomX, randomY).getCellType()!="#")
		{
			if (CheckShipCount(shipDictionary))
			{
				if (ship.AddShip(cellsArray))
				{
					ships.push_back(ship);

					shipDictionary[randomLenght] += 1;
					cout << shipDictionary[randomLenght] << endl;
				}
			}
		}
	}
}
 /*void CheckShipShooting(Cell selectedCell, CellArray cellsArray,
	vector<Ship> ships)
{
	if (selectedCell.IsShip && selectedCell.Enabled) //проверка на то, чтобы не считать лишние клики
	{
		Ship foundedShip =
			ships.FirstOrDefault(ship1 = > ship1.ShipId.Equals(selectedCell.ShipId));
		if (foundedShip != null)
		{
			selectedCell.Enabled = false;
			selectedCell.IsShot = true;
			if (foundedShip.CheckLostShip(cellsArray))
			{
				cellsArray.FixingBordersColor();
				ships.Remove(foundedShip); //удаляем корабль из списка
			}
		}
	}

	else if (selectedCell.Enabled)
	{
		selectedCell.IsShot = false;
		selectedCell.Enabled = false;
	}
}*/
int main()
{
	CellArray playerField, newField;

	Cell cell;

	int x = 0,  y = 0, verticalNumber,lenghtValue;
	bool verticalValue;
	int shipCount=0;
	playerField.ShowBattleField();
	RandomShipPositions(shipDictionary, playerField, player_vector);
	/*while (shipCount < 1)
	{

		system("cls");
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
			shipDictionary[lenghtValue - 1] += 1;
			shipCount++;
		}
		else
		{
			cout << "Невозможно размещение в этой позиции" << endl;
		}
		for (int i = 0; i< shipDictionary.size();  i++) {  // выводим их
			cout << shipDictionary[i] << endl;
		}

		system("pause");
		//cout << "Удаление корабля" << endl;
		//ship.DeleteShip(playerField);

	}*/
	playerField.ShowBattleField();


	system("pause");
	return 0;

}

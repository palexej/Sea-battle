// Морской бой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <random>
#include "Ship.h"
#include "Cell.h"
#include <mutex>
#include <thread>

#include "MyGraphic.h"
using namespace std;
vector<Ship> player_vector;
//словарь ячечек
map<int, int> playerDictionary = {
	{
		1, 0
	},
	{
		2, 0
	},
	{
		3, 0
	},
	{
		4, 0
	},
};
//проверка на то, что все корабли есть
bool CheckShipCount(map<int, int>& shipDictionary)
{
	if (shipDictionary[2] > 4 || shipDictionary[3] > 2 || shipDictionary[4] > 1)
	{
		return false;
	}

	return true;
}


//рандомная уствнока кораблей
void RandomShipPositions(map<int, int>& shipDictionary, CellArray& cellsArray, vector<Ship>& ships)
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом


	int startShipLenght = 2;

	while (shipDictionary[4] < 1) //пока не добавлен корабль длины 4
	{

		if (shipDictionary[2] == 4)
		{
			startShipLenght = 3;
		}

		if (shipDictionary[3] == 2)
		{
			startShipLenght = 4;
		}
		uniform_int_distribution<int> randomShipLenght(1, 10); //генерация чисел в указанном интервале
		int randomX = randomShipLenght(rd);
		int randomY = randomShipLenght(rd);

		uniform_int_distribution<int> randomVerticalOrientation(0, 1); //генерация чисел в указанном интервале

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


		//если корабль можно добавить, то добавляем его на поле и указываем это в списке кораблей
		Ship ship(randomX, randomY, randomVertical, randomLenght, 1);
		
			if (CheckShipCount(shipDictionary))
			{
				if (ship.AddShip(cellsArray))
				{
					ships.push_back(ship);
					shipDictionary[randomLenght] += 1;
				}
			}
		
	}
}

bool CheckShipShooting(Cell& selectedCell, CellArray& cellsArray,  vector<Ship>& ships,map<int,int> &dictionary)
{
	string isShip = "#";
	string isMiss = "$";
	vector<Ship>::iterator it;

	bool isFound = false;
	for (it = ships.begin(); it != ships.end(); ++it)//ищём по айди корабль среди вектора
	{
		if (it->getID() == selectedCell.getCellID())
		{
			isFound = true;
			cout << "Попадание" << endl;
			cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "*");
			if (it->CheckLostShip(cellsArray)) //если корабль убит, удаляем его из словаря
			{
				cout << "Корабль уничтожен" << endl;

				dictionary[it->getLenght()]-=1;

			}

		}
	}
	if (!isFound)
	{
		cout << "Промах" << endl;
		cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "$");
	}
	return isFound;
}

bool MakeRandomAIShot(CellArray& cellsArray, vector<Ship> ships,map<int,int> dictionary)
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом


	int randomX = 0, randomY = 0;

	int maxGenerateValue = Cell::CELL_COUNT - 1;
	int minGenerateValue = 1;
	uniform_int_distribution<int> randomShipPosition(1, maxGenerateValue); //генерация чисел в указанном интервале


	Cell aiCell;

	//выстрелы рандомные, но не видится корабль
	bool isBurnShipFound = false;
	Ship burnShip(0, 0, true, 2, -1);
	string isBurnShip = "*";
	string isEmpty = "?";
	vector<Ship>::iterator burnShipIterator;


		bool rightGenerationFlag = true;
		 randomX = randomShipPosition(rd);
		 randomY = randomShipPosition(rd);
		while (rightGenerationFlag)
		{
			if (cellsArray.GetCellByIndex(randomX, randomY).getCellType() == "*" || cellsArray.
				GetCellByIndex(randomX, randomY).getCellType() == "@"
				|| cellsArray.GetCellByIndex(randomX, randomY).getCellType() == "$" || cellsArray.
				GetCellByIndex(randomX, randomY).getCellType() == "#")
			{
				randomX = randomShipPosition(rd);
				randomY = randomShipPosition(rd);
			}
			else
			{
				rightGenerationFlag = false;
			}
		}
		Cell shotCell(randomX, randomY, "", -1);
		string checkThisId = cellsArray.GetCellByIndex(randomX, randomY).getCellType();
		if (checkThisId != "?" && checkThisId != "@" && checkThisId != "$" && checkThisId != "*")
		{
			shotCell.setCellID(stoi(checkThisId));
		}

		return CheckShipShooting(shotCell, cellsArray, ships, dictionary);
	

}

//игрок делает выстрел по координатам
bool MakePlayerShot(CellArray& cellsArray, vector<Ship> ships,map<int,int> &dictionary)
{
	
	cout << "х и у для выстрела:" << endl;
	int shotX, shotY;
	cin >> shotX >> shotY;
	Cell shotCell(shotX, shotY, "", -1);
	string checkThisId = cellsArray.GetCellByIndex(shotX, shotY).getCellType();
	if (checkThisId != "?" && checkThisId != "@" && checkThisId != "$" && checkThisId != "*")
	{
		shotCell.setCellID(stoi(checkThisId));
	}
	return CheckShipShooting(shotCell, cellsArray, ships, dictionary);
	
}
//определение того, что все корабли убиты
bool CheckShipDictionary(map<int,int> &shipDictionary)
{
	int equalsCounter = 0;
	int maxShip = 5;
	for (int i = 0; i < shipDictionary.size(); i++)
	{
		if(shipDictionary[i]==0)
		{
			equalsCounter++;
		}
	}
	if (equalsCounter== maxShip)
	{
		return false;
	}
	return true;
}

int main()
{
	CellArray playerField, botField;

	Cell cell;

	map<int, int> botDictionary = playerDictionary;
	vector<Ship> bot_vector;

	RandomShipPositions(botDictionary, botField, bot_vector);//рандомная расстановка кораблей
	int playerOffset = 0;
	int botOffset = 750;
	

	RandomShipPositions(playerDictionary, playerField, player_vector);
	
	//выстрелы компа
	while (CheckShipDictionary(botDictionary) && CheckShipDictionary(playerDictionary))
	{
	
		MyGraphic my_graphic;


		do
		{
			my_graphic.ShowFieldWindow(true, playerOffset, botOffset, playerField, botField);//отображение изменения поля до тех пор, пока не промазали
		}
		while (MakePlayerShot(botField, bot_vector, botDictionary));


		do
		{
			my_graphic.ShowFieldWindow(true, playerOffset, botOffset, playerField, botField);
		} while (MakeRandomAIShot(playerField, player_vector, playerDictionary));
	}
	if (!CheckShipDictionary(botDictionary))
	{
		cout << "Победа  игрока" << endl;
	}
	else
	{
		cout << "Победа компьютера" << endl;
	}

	system("pause");
	return 0;
}


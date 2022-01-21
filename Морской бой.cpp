// Морской бой.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <random>
#include "Ship.h"
#include "Cell.h"
#include <string.h>
#include <algorithm>
#include <mutex>
#include <thread>

#include "MyGraphic.h"
using namespace std;
vector<Ship> player_vector;
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

bool CheckShipCount(map<int, int>& shipDictionary)
{
	if (shipDictionary[2] > 4 || shipDictionary[3] > 2 || shipDictionary[4] > 1)
	{
		return false;
	}

	return true;
}

struct PCout
{
	static std::mutex& Mutex()
	{
		static std::mutex mut;
		return mut;
	}
};

#define thread_cout(msg)\
    PCout::Mutex().lock(), msg, PCout::Mutex().unlock()

void RandomShipPositions(map<int, int>& shipDictionary, CellArray& cellsArray, vector<Ship>& ships)
{
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом


	int startShipLenght = 2;

	while (shipDictionary[4] < 1) //пока не добавлен корабль длины 4
	{
		/*if (playerDictionary[1] == 4)
		{
			startShipLenght = 2;
		}*/
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


		Ship ship(randomX, randomY, randomVertical, randomLenght, 1);
		//if (cellsArray.GetCellByIndex(randomX, randomY).getCellType()!="#")
		{
			if (CheckShipCount(shipDictionary))
			{
				if (ship.AddShip(cellsArray))
				{
					ships.push_back(ship);

					shipDictionary[randomLenght] += 1;
					//cout << playerDictionary[randomLenght] << endl;
				}
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
	for (it = ships.begin(); it != ships.end(); ++it)
	{
		if (it->getID() == selectedCell.getCellID())
		{
			isFound = true;
			cout << "Попадание" << endl;
			cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "*");
			if (it->CheckLostShip(cellsArray)) //если корабль убит
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


	//if (!isBurnShipFound) //если раненый корабль не найден, то стреляем туда, куда это можно сделать
	{
		bool rightGenerationFlag = true;
		int randomX = randomShipPosition(rd);
		int randomY = randomShipPosition(rd);
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

	//если найден раненый корабль, проверяем соседние с ним ячейки
	/*if (isBurnShipFound)
	{
		for (int i = 0; i < CellArray::CELL_COUNT; i++)
		{
			for (int j = 0; j < CellArray::CELL_COUNT; j++)
			{
				if (cellsArray.GetCellByIndex(i, j).getCellID()==cellsArray.GetCellByIndex(randomX, randomY).getCellID())
				{
					CheckShipShooting(cellsArray.GetCellByIndex(i, j), cellsArray, ships);
				}

			}
		}
	}*/
}


bool MakePlayerShot(CellArray& cellsArray, vector<Ship> ships,map<int,int> &dictionary)
{
	//cellsArray.ShowBattleField();
	cout << "х и у для выстрела:" << endl;
	int shotX, shotY;
	cin >> shotX >> shotY;
	//string myType=
	Cell shotCell(shotX, shotY, "", -1);
	string checkThisId = cellsArray.GetCellByIndex(shotX, shotY).getCellType();
	if (checkThisId != "?" && checkThisId != "@" && checkThisId != "$" && checkThisId != "*")//todo сделать проверку на то, чтобы нельзя было стрелять в уже выстреленную ячейку, а то крашится
	{
		shotCell.setCellID(stoi(checkThisId));
	}
	return CheckShipShooting(shotCell, cellsArray, ships, dictionary);
	
}

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

	int x = 0, y = 0, verticalNumber, lenghtValue;
	bool verticalValue;
	int shipCount = 0;

	map<int, int> botDictionary = playerDictionary;
	vector<Ship> bot_vector;

	RandomShipPositions(botDictionary, botField, bot_vector);
	int playerOffset = 0;
	int botOffset = 750;
	/*
	char choise;
	cout << "Выберите способ расстановки кораблей:\n1. Автоматическая.\n2. Вручную" << endl;
	cin >> choise;
	bool isCorrectChoise = true;
	*/

	RandomShipPositions(playerDictionary, playerField, player_vector);
	/*
	 while (isCorrectChoise)
	 {
		 switch (choise)
		 {

		 case '1':
		 {
			 RandomShipPositions(playerDictionary, playerField, player_vector);
			 isCorrectChoise = false;
			 break;
		 }


		 
		 case '2':
		 {
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
				 Ship ship(x, y, verticalValue, lenghtValue, 1);

				 if (ship.AddShip(playerField))
				 {
					 cout << "Корабль размещен" << endl;
					 playerDictionary[lenghtValue - 1] += 1;
					 shipCount++;
				 }
				 else
				 {
					 cout << "Невозможно размещение в этой позиции" << endl;
				 }
				 for (int i = 0; i < playerDictionary.size(); i++)
				 {  // выводим их
					 cout << playerDictionary[i] << endl;
				 }




				
			 }
			 break;
			default:
			 cout << "Неверное выбран пункт меню, повторите попытку" << endl;
			 break;
		 }
		 }*/



	
	//выстрелы компа
	while (CheckShipDictionary(botDictionary) && CheckShipDictionary(playerDictionary))
	{
		cout << "Игрок" << endl;
		for (int i = 0; i < playerDictionary.size(); i++)
		{  // выводим их
			cout << playerDictionary[i] << endl;
		}
		cout << "Бот" << endl;
		for (int i = 0; i < botDictionary.size(); i++)
		{  // выводим их
			cout << botDictionary[i] << endl;
		}

		MyGraphic my_graphic;
	


		do
		{
			my_graphic.ShowFieldWindow(true, playerOffset, botOffset, playerField, botField);
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


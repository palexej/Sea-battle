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
#include <algorithm> 
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
	

	int startShipLenght = 2;

 	while( shipDictionary[4]<1)//пока не добавлен корабль длины 4
	{
		/*if (shipDictionary[1] == 4)
		{
			startShipLenght = 2;
		}*/
		if (shipDictionary[2] == 4)
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
		//if (cellsArray.GetCellByIndex(randomX, randomY).getCellType()!="#")
		{
			if (CheckShipCount(shipDictionary))
			{
				if (ship.AddShip(cellsArray))
				{
					ships.push_back(ship);

					shipDictionary[randomLenght] += 1;
					//cout << shipDictionary[randomLenght] << endl;
				}
			}
		}
	}
}

 void CheckShipShooting(Cell &selectedCell, CellArray &cellsArray,
	vector<Ship> &ships)
{
	 string isShip = "#";
	 string isMiss = "$";
	 vector<Ship>::iterator it;
	
	 bool isFound = false;
		for (it = ships.begin(); it != ships.end(); ++it)
		{
			if (it->getID()==selectedCell.getCellID())
			{
				isFound = true;
				cout << "Попадание" << endl;
				cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "*");
				if(it->CheckLostShip(cellsArray))//если корабль убит
				{
					cout << "Корабль уничтожен" << endl;
					/*int int_to_remove = it->getID();
					if (it != end(ships))
					{
						ships.erase(it);
					}*/

				}
			
				//deadShip.CheckLostShip(cellsArray);
				
			}
		}
	 if (!isFound)
	 {
		 cout << "Промах" << endl;
		 cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "$");
	 } 
	

}
 void MakeRandomAIShot(CellArray& cellsArray, vector<Ship> ships)
 {

	 random_device rd;
	 mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом


	 int randomX = 0, randomY = 0;

	 int maxGenerateValue = Cell::CELL_COUNT - 1;
	 int minGenerateValue = 1;
	 uniform_int_distribution<int> randomShipPosition(1, maxGenerateValue);//генерация чисел в указанном интервале


	
	 Cell aiCell;

	 //выстрелы рандомные, но не видится корабль
	 bool isBurnShipFound = false;
	 Ship burnShip(0,0,true,2,-1);
	 string isBurnShip = "*";
	 string isEmpty = "?";
	 vector<Ship>::iterator burnShipIterator;
	 /*for (int i = 0; i < CellArray::CELL_COUNT; i++)
	 {
		 for (int j = 0; j < CellArray::CELL_COUNT; j++)
		 {
			 //если есть корабль, в который мы попали и при этом он не считается убитым, то начинаем стрелять с клетки подбитого корабля
			 if (cellsArray.GetCellByIndex(i, j).getCellType() == isBurnShip )
			 {

				 for (burnShipIterator = ships.begin(); burnShipIterator != ships.end(); ++burnShipIterator)
				 {
					 if (burnShipIterator->getID() == cellsArray.GetCellByIndex(i, j).getCellID())
					 {
						 isBurnShipFound = true;
						 randomX = i;
						 randomY = j;
						 break;
					 }
				 }
			 }
		 }
	 }*/


	 //if (!isBurnShipFound) //если раненый корабль не найден, то стреляем туда, куда это можно сделать
	 {
		 bool rightGenerationFlag = true;
		 int randomX = randomShipPosition(rd);
		 int randomY = randomShipPosition(rd);
		 while (rightGenerationFlag)
		 {
			 if ( cellsArray.GetCellByIndex(randomX, randomY).getCellType() == "*"|| cellsArray.GetCellByIndex(randomX, randomY).getCellType()=="@"
				 || cellsArray.GetCellByIndex(randomX, randomY).getCellType() == "$")
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
		 if (checkThisId != "?"&& checkThisId!="@")
		 {
			 shotCell.setCellID(stoi(checkThisId));
		 }

		 CheckShipShooting(shotCell, cellsArray, ships);

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
int main()
{
	CellArray playerField, newField;

	Cell cell;

	int x = 0,  y = 0, verticalNumber,lenghtValue;
	bool verticalValue;
	int shipCount=0;
	
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
	//ручные выстрелы
	/*while (player_vector.size() > 0)
	{
		cout << "Размер вектора " << player_vector.size() <<endl;
		playerField.ShowBattleField();
		cout << "х и у для выстрела:" << endl;
		int shotX, shotY;
		cin >> shotX >> shotY;
		//string myType=
		Cell shotCell(shotX, shotY,"",-1);
		string checkThisId = playerField.GetCellByIndex(shotX, shotY).getCellType();
		if (checkThisId!="?")
		{
			shotCell.setCellID(stoi(checkThisId));
		}
	
		
		CheckShipShooting(shotCell, playerField, player_vector); 

		
	}*/
	
	//выстрелы компа
	while (player_vector.size() > 0)
	{
		
		playerField.ShowBattleField();
		MakeRandomAIShot(playerField, player_vector);
		system("pause");


	}
	
	system("pause");
	return 0;

}

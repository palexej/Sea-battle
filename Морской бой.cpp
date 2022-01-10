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
				}
			
				//deadShip.CheckLostShip(cellsArray);
				
			}
		}
	 if (!isFound)
	 {
		 cout << "Промах" << endl;
		 cellsArray.SetCellByIndex(selectedCell.getXcoord(), selectedCell.getYcoord(), "$");
	 } 
		/*vector<Ship>::iterator it;
		for ( it= ships.begin(); it < ships.end(); ++it)
		{
			cout << it->getID() << endl;
		}*/
		//auto findShip=find(ships.begin(), ships.end(), 1);

	//	cout << findShip << endl;
		/*if (foundedShip != null)
		{
			
			if (foundedShip.CheckLostShip(cellsArray))
			{
				//cellsArray.FixingBordersColor();
				ships.Remove(foundedShip); //удаляем корабль из списка
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
	
	while (player_vector.size() > 0)
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
	
		/*cout << "\nМассив:" << endl;
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				cout << playerField.GetCellByIndex(i, j).getCellType() << " ";
			}
			cout << "\n";
		}*/
		/*int cell_id = playerField.GetCellByIndex(shotX,shotY).getCellID();
		shotCell.setCellID(cell_id);*/
		CheckShipShooting(shotCell, playerField, player_vector); 

		
	}
	
	system("pause");
	return 0;

}

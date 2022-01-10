#include "pch.h"
#include "Ship.h"

#include <iostream>

#include "CellArray.h"

int SHIP_ID = 1;

Ship::Ship(int x = 0, int y = 0, bool isVertical = false, int lenght = 1, int id = 1)
{
	this->x_ = x;
	this->y_ = y;
	this->is_vertical_ = isVertical;
	this->lenght_ = lenght;
	this->id_ = id;
}


int Ship::getID()
{
	return id_;
}

void Ship::setID(int id)
{
	if (id >= 1 && id <= 9)
	{
		id_ = id;
	}
	else
	{
		id_ = 1;
	}
}

int Ship::getXcoord()
{
	return x_;
}

void Ship::setXcoord(int x)
{
	if (x >= 0 && x <= Cell::CELL_COUNT)
	{
		x_ = x;
	}
	else
	{
		x_ = 0;
	}
}

//Сделать оверрайт метода для координат х и у как вариант

int Ship::getYcoord()
{
	return y_;
}

void Ship::setYcoord(int y)
{
	if (y >= 0 && y <= Cell::CELL_COUNT)
	{
		y_ = y;
	}
	else
	{
		y_ = 0;
	}
}

bool Ship::CheckShipID(Cell& cell) //проверяем, чтобы корабли лежали от 1 до 9
{
	//для айдишников, которые не работают
	
	int integerNumber = char(cell.getCellType()[0]);
	if (integerNumber >= 49 && integerNumber <= 57)
	{
		return true;
	}
	return false;
/*
	if(cell.getCellType()=="#")
	{
		return true;
	}
	else
	{
		return false;
	}*/
}

bool Ship::AddShip(CellArray& cellsArray)
{
	//проверка на то, чтобы нельзя было установить корабль за границами массива
	int maxShipX = x_ + lenght_;
	int maxShipY = y_ + lenght_; //определяем, до какоко момента выполняется цикл

	const string IsShip = "#";

	if (x_ > 0 && y_ > 0) //проверка на выход за границы массива
	{
		if (is_vertical_)
		{
			if (maxShipX < CellArray::CELL_COUNT)
			{
				for (int i = x_; i < maxShipX; i++)
				{
					//odo при размещении вертикального и горизонтального кораблей в углу не происходит проверка
					if (CheckShipID(cellsArray.GetCellByIndex(i + 1, y_)) //сразу над кораблем
						|| CheckShipID(cellsArray.GetCellByIndex(i - 1, y_)) //сразу под кораблем
						|| CheckShipID(cellsArray.GetCellByIndex(i, y_ - 1)) //боковые
						|| CheckShipID(cellsArray.GetCellByIndex(i, y_ + 1))
						|| CheckShipID(cellsArray.GetCellByIndex(i + 1, y_ + 1)) //левый верхний и нижние углы
						|| CheckShipID(cellsArray.GetCellByIndex(i - 1, y_ + 1))
						|| CheckShipID(cellsArray.GetCellByIndex(i + 1, y_ - 1)) //правый верхний и нижние углы
						|| CheckShipID(cellsArray.GetCellByIndex(i - 1, y_ - 1)))
					{
						return false;
					}
				}

				
				//размещение кораблей после полной проверки
				for (int i = x_; i < maxShipX; i++)
				{
					
					cellsArray.SetCellByIndex(i, y_, std::to_string(SHIP_ID));
					cellsArray.GetCellByIndex(i,y_).setCellID(SHIP_ID);
				}

				id_ = SHIP_ID;
				
				SHIP_ID++;
				return true;
			}
		}
		else
		{
			if (maxShipY < Cell::CELL_COUNT)
			{
				for (int i = y_; i < maxShipY; i++)
				{
					if (CheckShipID(cellsArray.GetCellByIndex(x_ + 1, i)) //сразу над кораблем
						|| CheckShipID(cellsArray.GetCellByIndex(x_ - 1, i)) //сразу под кораблем
						|| CheckShipID(cellsArray.GetCellByIndex(x_, i - 1)) //боковые
						|| CheckShipID(cellsArray.GetCellByIndex(x_, i + 1))
						|| CheckShipID(cellsArray.GetCellByIndex(x_ + 1, i + 1)) //левый верхний и нижние углы
						|| CheckShipID(cellsArray.GetCellByIndex(x_ - 1, i + 1))
						|| CheckShipID(cellsArray.GetCellByIndex(x_ + 1, i - 1)) //правый верхний и нижние углы
						|| CheckShipID(cellsArray.GetCellByIndex(x_ - 1, i - 1)))
					{
						return false;
					}
				}
			
				for (int i = y_; i < maxShipY; i++)//вместо кораблей теперь айдишники
				{
					cellsArray.SetCellByIndex(x_,i, std::to_string(SHIP_ID));
					cellsArray.GetCellByIndex(x_,i).setCellID(SHIP_ID);
				
				}


				id_ = SHIP_ID;

				SHIP_ID++;
				return true;
			}
		}
	}

	return false;
}


bool Ship::CheckLostShip(CellArray& cellsArray)
{
	//проверка на то, чтобы нельзя было установить корабль за границами массива
	int maxShipX = x_ + lenght_;
	int maxShipY = y_ + lenght_; //определяем, до какоко момента выполняется цикл

	const string isShot = "*";
	const string shipSymbol = "#";
	const string noShip = "$";

	if (is_vertical_)
	{
		int countShot = 0;
		if (maxShipX < Cell::CELL_COUNT)
		{
			for (int i = x_; i < maxShipX; i++)
			{
				if (cellsArray.GetCellByIndex(i, y_) == isShot)
				{
					countShot++;
				}
			}
			if (countShot == lenght_)
			{
				for (int i = x_; i < maxShipX; i++)
				{
					//odo при размещении вертикального и горизонтального кораблей в углу не происходит проверка
					cellsArray.SetCellByIndex(i + 1, y_, noShip); //сразу над кораблем
					cellsArray.SetCellByIndex(i - 1, y_, noShip); //сразу под кораблем
					cellsArray.SetCellByIndex(i, y_ - 1, noShip); //боковые
					cellsArray.SetCellByIndex(i, y_ + 1, noShip);
					cellsArray.SetCellByIndex(i + 1, y_ + 1, noShip); //левый верхний и нижние углы
					cellsArray.SetCellByIndex(i - 1, y_ + 1, noShip);
					cellsArray.SetCellByIndex(i + 1, y_ - 1, noShip); //правый верхний и нижние углы
					cellsArray.SetCellByIndex(i - 1, y_ - 1, noShip);
				}


				//размещение кораблей после полной проверки
				for (int i = x_; i < maxShipX; i++)
				{
					cellsArray.SetCellByIndex(i, y_,shipSymbol);
				}

				return true;
			}
		}
		return false;
	}
	else
	{
		int countShot = 0;
		if (maxShipY < Cell::CELL_COUNT)
		{
			for (int i = y_; i < maxShipY; i++)
			{
				if (cellsArray.GetCellByIndex(x_, i) == isShot)
				{
					countShot++;
				}
			}
			if (countShot == lenght_)
			{
				for (int i = y_; i < maxShipY; i++)
				{
					cellsArray.SetCellByIndex(x_ + 1,i,noShip);//сразу над кораблем
					cellsArray.SetCellByIndex(x_ - 1, i,noShip); //сразу под кораблем
					cellsArray.SetCellByIndex(x_, i - 1,noShip); //боковые
					cellsArray.SetCellByIndex(x_, i + 1,noShip);
					cellsArray.SetCellByIndex(x_ + 1, i + 1,noShip); //левый верхний и нижние углы
					cellsArray.SetCellByIndex(x_ - 1, i + 1,noShip);
					cellsArray.SetCellByIndex(x_ + 1, i - 1,noShip); //правый верхний и нижние углы
					cellsArray.SetCellByIndex(x_ - 1, i - 1,noShip);
				}
			
				for (int i = y_; i < maxShipY; i++)
				{
					cellsArray.SetCellByIndex(x_, i,shipSymbol);
				}
			
				return true;
			}
		}

		return false;
	}
}
	void Ship::DeleteShip(CellArray& myArray)
	{
		if (is_vertical_)
		{
			for (int i = x_; i < x_ + lenght_; i++)
			{
				myArray.SetCellByIndex(i, y_, "?");
			}
		}
		else
		{
			for (int i = y_; i < y_ + lenght_; i++)
			{
				myArray.SetCellByIndex(x_, i, "?");
			}
		}
	}
	ostream& operator<<(std::ostream& out, const Ship& ship)
	{
		// Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
		out << ship.x_ << " " << ship.y_ << " " << ship.is_vertical_ << " " << ship.lenght_;

		return out;
	}

	bool Ship::getVertical()
	{
		return is_vertical_;
	}
	int Ship::getLenght()
	{
		return lenght_;
	}
	Ship::~Ship()
	{
	}

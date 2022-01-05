#pragma once
#include "CellArray.h"

class Ship
{
private:
	int x_;
	int y_;
	bool is_vertical_;
	int lenght_;
	int id_;
public:
	Ship();
	Ship(int x, int y, bool isVertical, int lenght, int id);
	int getID();
	void setID(int id);
	int getXcoord();
	void setXcoord(int x);
	int getYcoord();
	void setYcoord(int y);
	bool CheckShipID(Cell& cell);
	bool AddShip(CellArray& cellsArray);
	void DeleteShip(CellArray& myArray);
	bool getVertical();
	int getLenght();

	friend std::ostream& operator<< (std::ostream &out, const Ship &ship);
	~Ship();
};


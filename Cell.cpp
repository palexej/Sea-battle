#include "pch.h"
#include "Cell.h"


bool Cell::operator==(string str) const
{
	if (this->cell_type_==str)
	{
		return true;
	}
	return false;
}

int Cell::getCellID()
{
	return cellID;
}

void Cell::setCellID(int yourId)
{
	cellID = yourId;
}

Cell::Cell(int xCoord=0,int yCoord=0,string str="?",int id=-1)
{
	x_coord_ = xCoord;
	y_coord_ = yCoord;
	cell_type_ = str;
	cellID = id;
}




Cell& Cell::operator=(Cell* cell)
{
	x_coord_ = cell->x_coord_;
	y_coord_ = cell->y_coord_;
	cell_type_ = cell->cell_type_;
	cellID = cell->cellID;
	return *this;
}


Cell::Cell()
{
	x_coord_ = 0;
	y_coord_ = 0;
	cell_type_ = BORDERS;
	cellID = -1;
}

int Cell::getXcoord()
{
	return x_coord_;
}

int Cell::getYcoord()
{
	return y_coord_;
}

string Cell::getCellType()
{
	return cell_type_;
}

void Cell::setXcoord(int x)
{
	if (x>=0&&x<=CELL_COUNT)
	{
		x_coord_ = x;
	}
	else
	{
		x_coord_ = 0;
	}
}

void Cell::setYcoord(int y)
{
	if (y >= 0 && y <= CELL_COUNT)
	{
		y_coord_= y;
	}
	else
	{
		y_coord_ = 0;
	}
}

void Cell::setCellType(string symbol)
{
	cell_type_ = symbol;
}


Cell::~Cell()
{
}

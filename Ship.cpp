#include "pch.h"
#include "Ship.h"


Ship::Ship(int x = 0,int y=0,bool isVertical=false,int lenght=1)
{
	this->x = x;
	this->y = y;
	this->isVertical = isVertical;
	this->lenght = lenght;
}


Ship::~Ship()
{
}

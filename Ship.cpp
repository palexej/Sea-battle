#include "pch.h"
#include "Ship.h"

#include "CellArray.h"


Ship::Ship(int x = 0,int y=0,bool isVertical=false,int lenght=1)
{
	this->x_ = x;
	this->y_ = y;
	this->is_vertical_ = isVertical;
	this->lenght_ = lenght;
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
//������� �������� ������ ��� ��������� � � � ��� �������

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


bool Ship::AddShip(CellArray& cellsArray)
{
	//�������� �� ��, ����� ������ ���� ���������� ������� �� ��������� �������
	int maxShipX = x_ + lenght_;
	int maxShipY = y_ + lenght_; //����������, �� ������ ������� ����������� ����

	const string IsShip = "#";

	if (x_ > 0 && y_ > 0) //�������� �� ����� �� ������� �������
	{
		if (is_vertical_)
		{
			if (maxShipX < CellArray::CELL_COUNT)
			{
				for (int i = x_; i < maxShipX; i++)
				{
					//odo ��� ���������� ������������� � ��������������� �������� � ���� �� ���������� ��������
					if (cellsArray.GetCellByIndex(i + 1, y_)==IsShip//����� ��� ��������
						|| cellsArray.GetCellByIndex(i - 1, y_)==IsShip //����� ��� ��������
						|| cellsArray.GetCellByIndex(i, y_ - 1)==IsShip //�������
						|| cellsArray.GetCellByIndex(i, y_ + 1)==IsShip
						|| cellsArray.GetCellByIndex(i + 1, y_ + 1)==IsShip//����� ������� � ������ ����
						|| cellsArray.GetCellByIndex(i - 1, y_ + 1)==IsShip
						|| cellsArray.GetCellByIndex(i + 1, y_ - 1)==IsShip //������ ������� � ������ ����
						|| cellsArray.GetCellByIndex(i - 1, y_ - 1)==IsShip)
					{
						return false;
					}

				}

				/*Guid generateShipId = Guid.NewGuid(); //������� ID ������� � �������� ��� � ������
				ShipId = generateShipId.ToString();*/
				//���������� �������� ����� ������ ��������
				for (int i = x_; i < maxShipX; i++)
				{
					//cellsArray.GetCellByIndex(i, y_).setCellType("#");
					//cellsArray.SetCellByIndex(i,y_, "#");
					//cellsArray.GetCellByIndex(i, y_)==ShipId = generateShipId.ToString();
				}

				//����������, ����� ��������� ������ ������� � ������������ ��� ��������
				//�������������� ���������� �������, ����� ������ ���� ������� ������� ����� 2 � ������� �� ����� 4

				return true;
			}
		}
		else
		{
			if (maxShipY < Cell::CELL_COUNT)
			{
				for (int i = y_; i < maxShipY; i++)
				{
					if (cellsArray.GetCellByIndex(x_ + 1, i)==IsShip //����� ��� ��������
						|| cellsArray.GetCellByIndex(x_ - 1, i)==IsShip //����� ��� ��������
						|| cellsArray.GetCellByIndex(x_, i - 1)==IsShip //�������
						|| cellsArray.GetCellByIndex(x_, i + 1)==IsShip
						|| cellsArray.GetCellByIndex(x_ + 1, i + 1)==IsShip//����� ������� � ������ ����
						|| cellsArray.GetCellByIndex(x_ - 1, i + 1)==IsShip
						|| cellsArray.GetCellByIndex(x_ + 1, i - 1)==IsShip //������ ������� � ������ ����
						|| cellsArray.GetCellByIndex(x_ - 1, i - 1)==IsShip)
					{
						return false;
					}
				}
				/*
				Guid generateShipId = Guid.NewGuid(); //������� ID ������� � �������� ��� � ������
				ShipId = generateShipId.ToString();*/
				for (int i = y_; i < maxShipY; i++)
				{
					//cellsArray.GetCellByIndex(x_, i).setCellType("#");
					cellsArray.SetCellByIndex(x_, i, "#");
					//cellsArray.GetCellByIndex(x_, i)==ShipId = generateShipId.ToString();
				}

				return true;
			}
		}
	}

	return false;
}
 void Ship::DeleteShip(CellArray& myArray)
{
	if (is_vertical_)
	{
		for (int i = x_; i < x_ + lenght_; i++)
		{
			//myArray.GetCellByIndex(i, y_).IsShip = false;
			//myArray.GetCellByIndex(i, y_).ShipId = "-";
		}
	}
	else
	{
		for (int i = y_; i < y_ + lenght_; i++)
		{
			//myArray.GetCellByIndex(x_, i).IsShip = false;
			//myArray.GetCellByIndex(x_, i).ShipId = "-";
		}
	}
}
ostream& operator<< (std::ostream &out, const Ship &ship)
{
	// ��������� operator<< �������� ������ ������ Point, �� �� ����� ������ ������ � ������ Point
	out<<ship.x_<<" "<<ship.y_<<" "<<ship.is_vertical_<<" "<<ship.lenght_;

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

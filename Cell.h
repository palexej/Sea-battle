#pragma once
#include <cstring>
#include <string.h>
#include <string>
using namespace std;

class Cell
{

	//���� ������
private:
	int x_coord_;
	int y_coord_;
	string cell_type_;

	//@-��������� ������
	//? - ������ ����
	//# - �������
	//* - ���������
	//$ - ������
public:
	const string SHIP = "#";

	const string BORDERS = "@";
		
	 const string EMPTY = "?";
	
	static const int CELL_COUNT = 12;
	Cell(int xCoord, int yCoord, char symbol);
	char ShowCell();
	Cell(int xCoord, int yCoord, string str);
	::Cell& operator=(Cell* cell);
	Cell();
	int getXcoord();
	int getYcoord();
	string getCellType();
	void setXcoord(int x);
	void setYcoord(int y);
	void setCellType(string str);


	~Cell();
};
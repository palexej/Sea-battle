#pragma once
#include <cstring>
#include <string.h>
#include <string>
using namespace std;

class Cell
{

	//���� ������
protected:
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
	 const string MISS= "$";
	
	static const int CELL_COUNT = 12;
	char ShowCell();
	bool operator==(string str) const;
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

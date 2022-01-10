#pragma once
#include <cstring>
#include <string.h>
#include <string>
using namespace std;

class Cell
{

	//одна €чейка
protected:
	int x_coord_;
	int y_coord_;
	string cell_type_;
	int cellID;
	//@-граничные €чейки
	//? - просто поле
	//# - корабль
	//* - попадание
	//$ - промах
public:
	const string SHIP = "#";

	const string BORDERS = "@";
		
	 const string EMPTY = "?";
	 const string MISS= "$";
	  string SHOT = "*";
	static const int CELL_COUNT = 12;
	char ShowCell();
	bool operator==(string str) const;
	::Cell& operator=(Cell* cell);
	Cell();
	int getXcoord();
	int getYcoord();
	string getCellType();
	void setXcoord(int x);
	void setYcoord(int y);
	void setCellType(string str);
	void setCellID(int yourId);
	Cell(int xCoord, int yCoord, string str, int id);
	int getCellID();
	~Cell();
};

#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "CellArray.h"
using namespace sf;
using namespace std;
class MyGraphic
{
private:
	void DrawEmptyField(RenderWindow& window, int offsetX);
	void setShipsAndShots(CellArray cellArray, RenderWindow& window, int offsetX, bool isShipsShow);
	
public:

	
	MyGraphic();
	~MyGraphic();
	
	void ShowFieldWindow(bool isWindowActive, int playerOffset, int botOffset, CellArray playerCellArray, CellArray botCellArray);
};


#pragma once
class Ship
{
private:
	int x;
	int y;
	bool isVertical;
	int lenght;
public:
	Ship();
	Ship(int x, int y, bool isVertical, int lenght);
	~Ship();
};


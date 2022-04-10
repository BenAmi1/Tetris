#pragma once
#include "utilities.h"

class Point
{
private:
	int x = 0, y = 0;
	char figure = PLAYERS_FIGURE;

public:
	int  getX() const;
	int  getY() const;
	void setPoint(int _x, int _y);
	void  draw() const { gotoxy(x, y); cout << figure; }
	void UnPrintPoint() { gotoxy(x, y); putchar(BLANK); }
	void setShapeInPosition(Point* shape, int extraX, int extraY);
};
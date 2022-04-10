#include "Point.h"

int  Point::getX() const
{
	return x;
}

int  Point::getY() const
{
	return y;
}

void Point::setPoint(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Point::setShapeInPosition(Point* shape, int extraX, int extraY)
{
	for (size_t i = 0; i < BRICK_SIZE; i++)
	{
		shape[i].setPoint(shape[i].getX() + extraX, shape[i].getY() + extraY);
	}
}
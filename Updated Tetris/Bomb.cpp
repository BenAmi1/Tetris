#include "Bomb.h"


Bomb::Bomb(int startpoint)
{
	shape[0].setPoint(startpoint + 0, 0);
	shape[1].setPoint(startpoint + 0, 0);
	shape[2].setPoint(startpoint + 0, 0);
	shape[3].setPoint(startpoint + 0, 0);

	for (size_t i = 0; i < BRICK_SIZE; i++)
	{
		for (size_t j = 0; j < BRICK_SIZE; j++)
		{
			rotationArray[i][j].setPoint(0, 0); // initializing to zero -- there is no use in rotation in BOMB case
		}
	}
}



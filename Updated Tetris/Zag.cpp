#include "Zag.h"

Zag::Zag(int startPoint)
{
	shape[0].setPoint(startPoint + 2, 0);
	shape[1].setPoint(startPoint + 1, 0);
	shape[2].setPoint(startPoint + 1, 1);
	shape[3].setPoint(startPoint + 0, 1);

	rotationArray[0][0].setPoint(-1, 1);
	rotationArray[0][1].setPoint(0, 0);
	rotationArray[0][2].setPoint(-1, -1);
	rotationArray[0][3].setPoint(0, -2);

	rotationArray[1][0].setPoint(-1, -1);
	rotationArray[1][1].setPoint(0, 0);
	rotationArray[1][2].setPoint(1, -1);
	rotationArray[1][3].setPoint(2, 0);

	rotationArray[2][0].setPoint(1, -1);
	rotationArray[2][1].setPoint(0, 0);
	rotationArray[2][2].setPoint(1, 1);
	rotationArray[2][3].setPoint(0, 2);

	rotationArray[3][0].setPoint(1, 1);
	rotationArray[3][1].setPoint(0, 0);
	rotationArray[3][2].setPoint(-1, 1);
	rotationArray[3][3].setPoint(-2, 0);

	maxWidth = 3;
}



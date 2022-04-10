#include "Brick.h"
#include <time.h>

 void  Brick::printBrick() const
 {
	 for (int i = 0; i < BRICK_SIZE; i++)
		 shape[i].draw();
 }

 void Brick::UnPrintBrick() 
 {
	 for (int i = 0; i < BRICK_SIZE; i++)
		 shape[i].UnPrintPoint(); 
 }

 void Brick::DropBrick()
 {
	 UnPrintBrick();

	 for (size_t i = 0; i < BRICK_SIZE; i++)
		 shape[i].setPoint((shape[i]).getX(), (shape[i]).getY() + 1);

	 printBrick();
 }

 void Brick::rotateClockWise(int inTesting)
 {
	 UnPrintBrick();

	 int CurrMaxleft = getMaxLeft();

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 shape[i].setPoint(shape[i].getX() + rotationArray[rotationsCounter][i].getX(),
			 shape[i].getY() + rotationArray[rotationsCounter][i].getY());
	 }

	 if (getMaxLeft() != CurrMaxleft)
		 getShape()->setShapeInPosition(getShape(), CurrMaxleft - getMaxLeft() , 0);  // get shape back in position after rotate moved it from the pivot

	 setRotationNumber(1);

	 if(isBornedRotated == ROTATED_BY_PLAYER&& !inTesting)
		 printBrick();
 }

 void Brick::rotate_CounterClockWise()
 {
	 UnPrintBrick();

	 int Maxleft = getMaxLeft();

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 shape[i].setPoint(shape[i].getX() - rotationArray[rotationsCounter][i].getX(),
			 shape[i].getY() - rotationArray[rotationsCounter][i].getY());
	 }

	 if (getMaxLeft() != Maxleft)
		 getShape()->setShapeInPosition(getShape(), Maxleft - getMaxLeft(), 0); // get shape back in position after rotate moved it from the pivot

	 printBrick();
 }

 void Brick::goLeft()
 {
	 UnPrintBrick();
	 for (size_t i = 0; i < BRICK_SIZE; i++)
		 shape[i].setPoint(shape[i].getX() + LEFT, shape[i].getY());

	 printBrick();
 }

 void Brick::goRight()
 {
	 UnPrintBrick();
	 for (size_t i = 0; i < BRICK_SIZE; i++)
		 shape[i].setPoint(shape[i].getX() + RIGHT, shape[i].getY());

	 printBrick();
 }

 void Brick::dropDown(int level)
 {
	 UnPrintBrick();
	 for (size_t i = 0; i < BRICK_SIZE; i++)
		 shape[i].setPoint(shape[i].getX(), shape[i].getY() + level);

	 printBrick();
 }

 void Brick::setRotationNumber(int add)
 {
	 if (rotationsCounter + add < 0)
		 rotationsCounter = 3;
	 else
		 rotationsCounter = (rotationsCounter + add) % 4;
 }

 int Brick::getCurrentWidth() const
 {
	 int min = shape[0].getX();
	 int max = shape[3].getX();

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getX() < min)
			 min = shape[i].getX();

		 if (shape[i].getX() > max)
			 max = shape[i].getX();
	 }

	 return max - min+1;
 }

 Brick::Brick(const Brick& a)
 {
	 rotationsCounter = a.rotationsCounter;
	 isBornedRotated = a.isBornedRotated;

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 for (size_t j = 0; j < BRICK_SIZE; j++)
		 {
			 rotationArray[i][j] = a.rotationArray[i][j];
		 }
	 }

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 Point tmp = a.shape[i];
		 int x = tmp.getX();
		 int y = tmp.getY();
		 shape[i].setPoint(x,y);
	 }
	 maxWidth = a.maxWidth;
 }

 int Brick::getMaxLeft() const
 {
	 int offset = 0;
	 int min = shape[0].getX();

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getX() < min)
			 min = shape[i].getX();
	 }

	 return (min);
 }

 int Brick::getOffsetFromTop() const
 {
	 int maxY = shape[0].getY();
	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getY() < maxY)
		 {
			 maxY = shape[i].getY();
		 }
	 }

	 return -1*maxY;
 }

 int Brick::getShapeHeight() const
 {
	 int min = 19;
	 int max = 0;

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getY() < min)
			 min = shape[i].getY();
	 }

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getY() > max)
			 max = shape[i].getY();
	 }

	 return max - min;
 }

 int Brick::getMaxHeight() const
 {
	 int max = BOARD_LENGTH;

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getY() < max)
		 {
			 max = shape[i].getY();
		 }
	 }
	 return max;
 }

 int Brick::getLowestPoint() const 
 {
	 int max = 0;

	 for (size_t i = 0; i < BRICK_SIZE; i++)
	 {
		 if (shape[i].getY() > max)
		 {
			 max = shape[i].getY();
		 }
	 }
	 return max;
 }
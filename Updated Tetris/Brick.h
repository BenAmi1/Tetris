#pragma once
#include "utilities.h"
#include "Point.h"

using namespace std;

enum Brick_Type
{
	tall = 0, zig = 1, zag = 2, cube = 3, mini_plus = 4, normal_L = 5, inverted_L = 6
};

class Brick 
{
private:
	int rotationsCounter = 0;
	bool isBornedRotated = 0;

protected:
	Point rotationArray[4][4];
	Point shape[4];
	int maxWidth = 0;

public:
	Brick() {}
	Brick(const Brick& a);
	Point* getShape() { return shape; }
	Point* getRotationArray() { return rotationArray[rotationsCounter]; }
	void DropBrick();
	void setBornRotation(int x) { isBornedRotated = x; }
	void goLeft();
	void goRight();
	void dropDown(int level);
	void setRotationNumber(int add);
	void  printBrick() const;
	void UnPrintBrick() ;
	void setRotationZero() { rotationsCounter = 0; }
	int getMaxLeft() const;
	int getOffsetFromTop() const;
	int getShapeHeight() const;
	int getMaxHeight() const;
	int getLowestPoint() const;
	int getRotationNumber()const { return rotationsCounter % 4 ; }
	virtual ~Brick() { };
	virtual int getCurrentWidth() const;
	virtual void rotateClockWise(int inRunning);
	virtual void rotate_CounterClockWise();
	bool getBornRotation() { return isBornedRotated; }
};


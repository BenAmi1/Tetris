#pragma once
#include "Brick.h"

class Cube : public Brick
{
public:
	Cube(int startPoint);
	void  rotateClockWise(int inRunning) override { /*there is no use in rotation in CUBE case*/ }
	void  rotate_CounterClockWise() override {/*there is no use in rotation in CUBE case*/ }
	~Cube() {}
};
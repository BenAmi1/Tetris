#pragma once
#include "Brick.h"

class Bomb : public Brick
{
public:
	Bomb(int startpoint);
	void  rotateClockWise(int inrunning) override { /*there is no use in rotation in BOMB case*/}
	void  rotate_CounterClockWise() override  {/*there is no use in rotation in BOMB case*/ }
};
#include "Player.h"

Player::Player(int _startPoint)
{
	startPoint = _startPoint;
}

void Player::setDirection1(char key)
{
	switch(key)
	{
	case ('a'):
		this->brick->goLeft();
		break;
	case ('A'):
		this->brick->goLeft();
		break;
	case ('d'):
		this->brick->goRight();
		break;
	case ('D'):
		this->brick->goRight();
		break;
	case ('w'):
		this->brick->rotate_CounterClockWise();
		break;
	case ('W'):
		this->brick->rotate_CounterClockWise();
		break;
	case ('s'):
		this->brick->rotateClockWise(PLAY_MODE);
		break;
	case ('S'):
		this->brick->rotateClockWise(PLAY_MODE);
		break;
	case ('x'):
		this->brick->dropDown(getDropLevel());
		break;
	case ('X'):
		this->brick->dropDown(getDropLevel());
		break;
	}
}

void Player::setDirection2(char key)
{

	switch (key)
	{
	case ('j'):
		this->brick->goLeft();
		break;
	case ('J'):
		this->brick->goLeft();
		break;
	case ('l'):
		this->brick->goRight();
		break;
	case ('L'):
		this->brick->goRight();
		break;
	case ('i'):
		this->brick->rotate_CounterClockWise();
		break;
	case ('I'):
		this->brick->rotate_CounterClockWise();
		break;
	case ('k'):
		this->brick->rotateClockWise(PLAY_MODE);
		break;
	case ('K'):
		this->brick->rotateClockWise(PLAY_MODE);
		break;
	case ('m'):
		this->brick->dropDown(getDropLevel());
		break;
	case ('M'):
		this->brick->dropDown(getDropLevel());
		break;
	}
}


Brick* Player::getNewBrick() 
{
	srand(time(nullptr));
	int brickType = rand() % NUBMER_OF_BRICK_TYPES;
	int oneToTwenty = rand() % BOMB_APPEARENCE_PROBABILITY;
	
	if (!oneToTwenty)
		brick = new Bomb(startPoint);
	else
	{
		switch (brickType)
		{
		case(tall):
			brick = new Tall(startPoint);
			return brick; 
		case(zig):
			brick = new Zig(startPoint);
			return brick; 
		case(zag):
			brick = new Zag(startPoint);
			return brick; 
		case(cube):
			brick = new Cube(startPoint);
			return brick; 
		case(mini_plus):
			brick = new MiniPlus(startPoint);
			return brick; 
		case(normal_L):
			brick = new Normal_L(startPoint);
			return brick;
		case(inverted_L):
			brick = new Inverted_L(startPoint);
			return brick;
		}
	}

	return brick;
}
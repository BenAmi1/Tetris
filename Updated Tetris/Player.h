#pragma once
#include "Cube.h"
#include "Inverted_L.h"
#include "Bomb.h"
#include "MiniPlus.h"
#include "Normal_L.h"
#include "Zag.h"
#include "Zig.h"
#include "Tall.h"

inline bool ValidKey_P1(char key);
inline bool ValidKey_P2(char key);

bool ValidKey_P1(char key)
{
	return (key == 'a' || key == 's' || key == 'd' || key == 'w' || key == 'x' || key == 'A' || key == 'S' ||
		key == 'D' || key == 'W' || key == 'X');
}

bool ValidKey_P2(char key)
{
	return(key == 'j' || key == 'l' || key == 'k' || key == 'i' || key == 'm' || key == 'J' || key == 'L' ||
		key == 'K' || key == 'I' || key == 'M');
}


class Player 
{
	Brick* brick = nullptr;
	int bombDropLevel = 0;
	int score = 0;
	int startPoint;
	int bricksCounter = 0;

public:
	Player(int startpoint);
	void setDirection1(char key);
	void setDirection2(char key);
	Brick* getMyBrick() const { return brick; }
	void setDropLevel(int _level) { bombDropLevel=_level; }
	int getDropLevel() const { return bombDropLevel; }
	int getScore() const { return score; }
	void setBricksCounter() { bricksCounter += 1; }
	int getBricksCounter() { return bricksCounter; }
	void setScore() { score += 10; }
	Brick* getNewBrick();
};
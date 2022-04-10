#pragma once
#include "Player.h"

inline Point getRangeOfExplosion(int x, int leftBorder);
inline int getRandomInsertToComputedMove(int x);

class Board
{
private:
	char figure = BOARD_FIGURE;
	int lengh = BOARD_LENGTH, width = BOARD_WIDTH;
	char board[BOARD_LENGTH][BOARD_WIDTH] = {};
	Player player_1;
	Player player_2;
	Point gps1;
	Point gps2;

public:
	Board(int startPoint1, int startPoint2) : player_1(startPoint1), player_2(startPoint2) { initBoard(); }
	void initBoard();
	void printBoard();
	void createBoard();
	void Create_Print_Boards();
	void updateBoard(Point* shape);
	void winning(int Player) const;
	void timePause() const;
	void Printscore() const;
	void bombExplosion(Point coordinate);
	void HandleHit2(Point* CurrShape1, Point* CurrShape2, char key_2, bool player_1Turn);
	void computedMove(int leftBorder, Brick* CurrentBrick, char tempboard[BOARD_LENGTH][BOARD_WIDTH]);
	void updateTemporaryBoard(Point* shape, char tempboard[BOARD_LENGTH][BOARD_WIDTH]);
	void endGame() const;
	void unUpdateTestBoard(char tempboard[BOARD_LENGTH][BOARD_WIDTH], Point* shape);
	void getPath(int leftend, int optimalX, int initPoint, int bestRotation, bool fullLine);
	void updateGPSinRandomMove(int leftBorder);
	void DeleteRow(int i, int j);
	void  handleComputedBomb(int leftBorder, int startPoint);
	bool CheckMove1(Point* shape, char key);
	bool CheckMove2(Point* shape, char key);
	bool checkSides(Point* shape, int direction);
	bool NotBlockedFromBelow(Point* shape);
	bool checkForFullLines();
	bool checkRotation(Point* shape, Point* deltas);
	bool HandleHit1(Point* CurrShape1, Point* CurrShape2, char key_1, int mode);
	bool BlanksBlockedCounter(Point* shape, char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftBorder) const;
	bool isBoardIsGettingFilledUp(char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftBorder);
	int  RunGame(int Mode);
	int  menu(int MODE);
	int  decode(char key) const;
	int  ThereIsWinning();
	int  checkPossibleLevel(Point* shape) const;
	int  difficulty() const;
	int  gameMode() const;
	int  checkForFullLineInSingleBoard(char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftIndex) const;
	int  idealPointForBomb(Point p) const;
	void updateBricksCounter(int p);
	char decipherGPS(Point& gps, int player1);
	Point checkHeighestPossibleLevel(int leftBorder);
};

int getRandomInsertToComputedMove(int difficultyLevel)
{
	int random = 1;
	srand(time(nullptr));

	if (difficultyLevel == GOOD)
		random = rand() % 40;
	else if (difficultyLevel == NOVICE)
		random = rand() % 10;

	return random;
}

Point getRangeOfExplosion(int x, int leftBorder)
{
	int leftIndex = leftBorder + 1;
	int rightIndex = leftBorder + SIZE_OF_ROW;
	int rightX = x;
	int leftX = x;
	Point optimal;

	optimal.setPoint(leftX - BOMB_RANGE_ONE_SIDE, rightX + BOMB_RANGE_ONE_SIDE);

	while (leftX - BOMB_RANGE_ONE_SIDE - leftIndex < 0)
		leftX++;

	while (rightX + BOMB_RANGE_ONE_SIDE - rightIndex > 0)
		rightX--;

	optimal.setPoint(leftX- BOMB_RANGE_ONE_SIDE, rightX+ BOMB_RANGE_ONE_SIDE);

	return optimal;
}
#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"

int main()
{
	int gameStatus = gameOn;
	Board gameBoard(PLAYER_1_X_INIT_POINT, PLAYER_2_X_INIT_POINT);

	hideCurser();

	while (gameStatus == gameOn)
	{
		gameStatus = gameBoard.menu(NEW_GAME);

		cls();

		if (gameStatus == EXIT_GAME)
		{
			gameStatus = END_GAME;
		}

		if (gameStatus!= END_GAME)
		{
			gameBoard = { PLAYER_1_X_INIT_POINT, PLAYER_2_X_INIT_POINT };
			gameStatus = gameBoard.RunGame(gameStatus);
		}

		cls();
	}
	return END_GAME;
}




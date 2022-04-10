#include "Board.h"

void Board::createBoard() 
{
	for (int i = 0; i < lengh; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == LINE_ZERO && (j == 0 || j == BOARD_1_WIDTH - 1 || j == BOARD_2_START_INDEX || j == width - 1))
				board[i][j] = figure;
			else if (i == LINE_ZERO)
				board[i][j] = BLANK;
			else if ((i == lengh - 1) && (j< BOARD_1_WIDTH-1 || j>BOARD_2_START_INDEX))
				board[i][j] = figure;
			else if (i > LINE_ZERO)
			{
				if (j == COLUMN_ZERO || j == BOARD_1_WIDTH-1 || j== BOARD_2_START_INDEX || j== width-1)
					board[i][j] = figure;
				else
					board[i][j] = BLANK;
			}
		}
	}
}


void Board::printBoard() 
{
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
			putchar(board[i][j]);

		putchar('\n');
	}

	Printscore();
}


void Board::Create_Print_Boards()
{
	createBoard();
	printBoard();
}


int  Board::difficulty() const // sets game difficulty. contains option for normal game (beginner mode)
{
	char op;
	cout << "Choose difficulty level: \nBest: Press (1) \n";
	cout << "Good: Press (2) \n";
	cout << "Novice: Press (3) \n";

	op = _getch();

	while (op != '1' && op != '2' && op != '3')
	{
		cls();
		cout << "Wrong key was pressed, please Press (1) OR (2) OR (3)"<< endl << endl;
		cout <<"Best: (1) \n";
		cout << "Good : (2) \n";
		cout << "Novice : (3)\n";
		op = _getch();
	}

	switch (op)
	{
	case('1'):
		cls();
		return BEST;
	case('2'):
		cls();
		return GOOD;
	case('3'):
		cls();
		return NOVICE;
	default:
		return DEFAULT_VALUE; // In order to return a value from all control paths
	}
}

void  Board::timePause() const
{
	Sleep(TIME_PAUSE);
}

bool Board::HandleHit1(Point* CurrShape1, Point* CurrShape2, char key_1, int mode)
{
	bool player_1_played = false;

	if (ValidKey_P1(key_1) && CheckMove1(CurrShape1, key_1) && key_1 != DOWN)
	{
		player_1.setDirection1(key_1); // if key belongs to player 1, and the move is legal  - move the brick
		player_1_played = true;
	}

	if (mode == HUMAN_VS_HUMAN)
	{
		if (ValidKey_P2(key_1) && CheckMove2(CurrShape2, key_1) && key_1 != DOWN)
			player_2.setDirection2(key_1); // if key belongs to player 2, and the move is legal - move the brick

	}

	return player_1_played;
}

void Board::HandleHit2(Point* CurrShape1, Point* CurrShape2, char key_2, bool player_1Turn)
{
	if (player_1Turn == true) // player 1 made move - now player's 2 turn
		if (ValidKey_P2(key_2) && CheckMove2(CurrShape2, key_2) && key_2 != DOWN)
			player_2.setDirection2(key_2); // if key belongs to player 2, and the move is legal - move the brick
		else // player 2 made a move, now it's player's 1 turn
			if (ValidKey_P1(key_2) && CheckMove1(CurrShape1, key_2) && key_2 != DOWN)
				player_1.setDirection1(key_2); // if key belongs to player 1, and the move is legal  - move the brick
}

void Board::unUpdateTestBoard(char tempboard[BOARD_LENGTH][BOARD_WIDTH], Point* tmpshape)
{
	for (int i = 0; i < BRICK_SIZE; i++)
		tempboard[tmpshape[i].getY()][tmpshape[i].getX()] = BLANK;
}


Point Board::checkHeighestPossibleLevel(int leftBorder)
{
	size_t range;
	Point res;
	res.setPoint(0, 0);

	if (leftBorder)
		range = BOARD_WIDTH-2;
	else
		range = BOARD_1_END_PLAYING_INDEX;

	for (size_t i = 0; i < BOARD_LENGTH; i++)
	{
		for (size_t j = leftBorder; j <= range; j++)
		{
			if (board[i][j] == PLAYERS_FIGURE)
			{
				res.setPoint(j, i);
				return res;
			}
		}
	}

	return res;
}

int Board::idealPointForBomb(Point p) const
{
	int i = 0;
	while (board[p.getY()+i][p.getX()] == BLANK)
		i++;

	return i;
}


void Board::handleComputedBomb(int leftBorder, int startPoint) 
{
	Point heighestPoint = checkHeighestPossibleLevel(leftBorder);

	int x = heighestPoint.getX();
	int y = heighestPoint.getY();
	Point p = getRangeOfExplosion(x, leftBorder);
	Point tempBomb;
	int max = 0, tmpHeight = 0, index = x;

	for (int i = p.getX(); i <= p.getY(); i++)
	{
		tempBomb.setPoint(i, y);
		tmpHeight = idealPointForBomb(tempBomb);
		if (tmpHeight > max && tmpHeight<=BOMB_RANGE_ONE_SIDE)
		{
			max = tmpHeight;
			index = i;
		}
	}

	getPath(leftBorder, index, startPoint, 0, 0);
}


bool Board::BlanksBlockedCounter(Point * shape ,char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftBorder) const
{
	for (size_t i = 0; i < BRICK_SIZE; i++)
		if (tempboard[shape[i].getY() + GO_DOWN_ONE_ROW][shape[i].getX()] == BLANK)
			return true;

	return false;
}


void Board::computedMove(int leftBorder, Brick* CurrentBrick, char tempboard[BOARD_LENGTH][BOARD_WIDTH])
{
	int leftIndex, rightIndex, startPoint;

	Brick tmpBrick = *CurrentBrick;
	int Maxbuttom = 0, direction = 0, buttom = BOARD_LENGTH - 2, NumOfRotation = 0, shapeHeight = 0;
	int deeperOptionRotation = 0, deeperOptionX = 0, range, moveToLeft, pushUp, rowsDeletingRotation = 0;
	int rowsDeleted = 0, MaxRowDeleted = 0, RowsDeletingX = 0;
	bool nunOfBlockedBlanks = false, idealSpotFound = false, boardIsGettingHigh = false, fullLine = false;

	if (leftBorder!=BOARD_1_START_INDEX) // MOVE OF PLAYER 2 - RIGHT BOARD
	{
		leftIndex = BOARD_2_START_PLAYING_INDEX;
		rightIndex = BOARD_2_END_PLAYING_INDEX;
		startPoint = PLAYER_2_X_INIT_POINT;
	}
	else // MOVE OF PLAYER 1 - LEFT BOARD
	{
		leftIndex = BOARD_1_START_PLAYING_INDEX;
		rightIndex = BOARD_1_END_PLAYING_INDEX;
		startPoint = PLAYER_1_X_INIT_POINT;
	}

	RowsDeletingX = deeperOptionX = leftIndex;

	if ((typeid(*CurrentBrick)) == typeid(Bomb))
	{
		handleComputedBomb(leftBorder, startPoint); // putting the bomb in the best place -->near (and not on) the heigest tower
		return;
	}
	
	for (size_t i = 0; i < BRICK_SIZE; i++) // check all rotation of shape
	{
		pushUp = tmpBrick.getOffsetFromTop();
		if (i== FIRST_ITERATION) // put brick in its place in the middle of the board
			tmpBrick.getShape()->setShapeInPosition(tmpBrick.getShape(), -1 * (tmpBrick.getMaxLeft() - startPoint), pushUp);
		else 
		{
			tmpBrick.rotateClockWise(TEST_MODE);
			NumOfRotation++;
		}

		shapeHeight = tmpBrick.getShapeHeight(); // getting 
		pushUp = tmpBrick.getOffsetFromTop(); // calculate how much rows the brick should go back to the top after rotation
		moveToLeft = -1 * (tmpBrick.getMaxLeft() - leftIndex); // calculate how much left can we go to the most leftern index
		range = tmpBrick.getCurrentWidth(); // get the whdth of the shape
		tmpBrick.getShape()->setShapeInPosition(tmpBrick.getShape(), moveToLeft, pushUp); // take the shape to far left index
		for (int j = 0; j <= SIZE_OF_ROW - range; j++) // check all possible position in the specific rotate iteration
		{
			buttom = checkPossibleLevel(tmpBrick.getShape()); // how deep can we go in the board
			tmpBrick.getShape()->setShapeInPosition(tmpBrick.getShape(), NO_CHANGE_IN_SIDES, buttom); // go the the deepest spot in the specific column (j)
			updateTemporaryBoard(tmpBrick.getShape(), tempboard); // update the board with the change --> in order to check if lines are getting full
			nunOfBlockedBlanks=BlanksBlockedCounter(tmpBrick.getShape(), tempboard, leftBorder); // how much (if any) blanks on board was blockede (holes were created?)
			rowsDeleted = checkForFullLineInSingleBoard(tempboard, leftBorder); // calculate how much (if any) rows have been filled
			if (rowsDeleted!=0) // row/s have been filled
			{
				fullLine = true;
				if (rowsDeleted > MaxRowDeleted) // we found a spot which deleting more rows
				{
					MaxRowDeleted = rowsDeleted;
					RowsDeletingX = tmpBrick.getMaxLeft(); // save the spot on the board (column [j])
					rowsDeletingRotation = NumOfRotation;  // save how many rotation
				}
			}

			if (Maxbuttom < buttom + shapeHeight && (!nunOfBlockedBlanks || boardIsGettingHigh) && !fullLine) // no full line, a deeper spot was found
			{
				Maxbuttom = buttom + shapeHeight;
				deeperOptionX = tmpBrick.getMaxLeft();// save the spot on the board (column [j])
				deeperOptionRotation = NumOfRotation;// save how many rotation
			}

			unUpdateTestBoard(tempboard, tmpBrick.getShape()); // unUpdate the board after the update, in order to check the next possible spot
			if (j != SIZE_OF_ROW - range) // 
				tmpBrick.getShape()->setShapeInPosition(tmpBrick.getShape(), RIGHT, -1 * buttom); // take the brick back up, and one column to the right to check next spot
			else// last iteration on this specific rotation
			{
				if (i == LAST_ROTATION_ITERATION)
					break;
				tmpBrick.getShape()->setShapeInPosition(tmpBrick.getShape(),( 3*LEFT), (-1 * buttom) + GO_DOWN_ONE_ROW); 
			}
		}
		//isBoardIsGettingFilledUp(tempboard, leftBorder) ? boardIsGettingHigh = true : boardIsGettingHigh = false; // if the board is starting to get full, 
                                                                                              //change the priority and go deeper even if
		                                                                                             //blank are being blocked
	}

	if (fullLine)	// if we can fill a line, select this path.
		getPath(leftBorder, RowsDeletingX, startPoint, rowsDeletingRotation, fullLine);
	else
		getPath(leftBorder, deeperOptionX, startPoint, deeperOptionRotation, fullLine); // go deepest / don't block blanks

}

bool Board::isBoardIsGettingFilledUp(char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftBorder) //Checks if board is starting to get filled up, by checking if rows 10 / 11 if being occupied
{
	int counter1 = 0;
	int counter2 = 0;

	for (int i = leftBorder + 1; i < leftBorder + 12; i++)
	{
		if (tempboard[11][i] == PLAYERS_FIGURE)
			counter1++;

		if (tempboard[10][i] == PLAYERS_FIGURE)
			counter2++;
	}

	if (counter1 >= 2 || counter2>=2)
		return true;

	return false;
}

void Board::getPath(int leftBorder, int optimalX, int initPoint, int bestRotation, bool fullLine)// update GPS in the path, via point -->X is left / right, Y is number of rotations
{
	int direction; 
	if (fullLine) // line is full
	{
		if (leftBorder!=BOARD_1_START_INDEX) // MOVE OF PLAYER 2 - RIGHT BOARD
		{
			direction = optimalX - initPoint; 
			gps2.setPoint(direction, bestRotation);
		}
		else
		{
			direction = optimalX - initPoint;
			gps1.setPoint(direction, bestRotation);
		}
	}
	else
	{
		if (leftBorder!=BOARD_1_START_INDEX)// MOVE OF PLAYER 2 - RIGHT BOARD
		{
			direction = optimalX  - initPoint;
			gps2.setPoint(direction, bestRotation);
		}
		else // MOVE OF PLAYER 1 - LEFT BOARD
		{
			direction = optimalX - initPoint;
			gps1.setPoint(direction, bestRotation);
		}
	}
}


void Board::updateTemporaryBoard(Point* shape, char tempboard[BOARD_LENGTH][BOARD_WIDTH]) // make the brick part of the board after it stopped
{
	for (int i = 0; i < BRICK_SIZE; i++)
		tempboard[shape[i].getY()][shape[i].getX()] = PLAYERS_FIGURE;
}


char Board::decipherGPS(Point& gps, int player1) // get next move from GPS -->X is left / right, Y is number of rotations
{
	if (gps.getY() > 0) // THERE IS A ROTATION 
	{
		gps.setPoint(gps.getX(), gps.getY() - 1); // delete one rotation from the path
		return player1 ? 'k' : 's';
	}

	if (gps.getX() != 0) 
	{
		if (gps.getX() > 0) // brick needs to go right
		{
			gps.setPoint(gps.getX() - 1, 0);
			return player1 ? 'l' : 'd';
		}
		else // brick needs to go left
		{
			gps.setPoint(gps.getX() + 1, 0); 
			return player1 ? 'j' : 'a';
		}
	}

	return player1 ? 'm' : 'x';
}

int Board::checkForFullLineInSingleBoard(char tempboard[BOARD_LENGTH][BOARD_WIDTH], int leftBorder) const
{
	int counter = 0;
	size_t range;
	int rowsCounter = 0;
	if (leftBorder != BOARD_1_START_INDEX)
		range = BOARD_2_END_PLAYING_INDEX;
	else
		range = BOARD_1_END_PLAYING_INDEX;

	for (size_t i = 0; i < BOARD_LENGTH; i++)
	{
		for (size_t j = leftBorder+1; j <= range; j++)
		{
			if (tempboard[i][j] == PLAYERS_FIGURE)
			{
				counter++;
				if (counter == SIZE_OF_ROW)
					rowsCounter++;
			}
		}
		counter = 0;
	}
	return rowsCounter;
}


void Board::updateGPSinRandomMove(int leftBorder)
{
	srand(time(nullptr));

	int randomRotate = rand()% RANDOM_ROTATION;
	int randomGoToSides = rand()% RANDOM_HORIZONAL_MOVE;
	int randRightORLeft = rand() % RANDOM_LEFT_OR_RIGHT;

	if (leftBorder != BOARD_1_START_INDEX)
	{
		if (randRightORLeft)
			gps2.setPoint(randomGoToSides, randomRotate);
		else
			gps2.setPoint(-1*randomGoToSides, randomRotate);
	}
	else
	{
		if (randRightORLeft)
			gps1.setPoint(randomGoToSides, randomRotate);
		else
			gps1.setPoint(-1 * randomGoToSides, randomRotate);
	}
}

void Board::updateBricksCounter(int p)
{
	if (!p)
	{
		gotoxy(COLUMN_ZERO, BOARD_LENGTH + 4);
		player_1.setBricksCounter();
		cout << "BRICKS COUNTER: " << player_1.getBricksCounter();
	}

	else
	{
		gotoxy(OFFSET_BOARD_1_2 - 1, BOARD_LENGTH + 4);
		player_2.setBricksCounter();
		cout << "BRICKS COUNTER : " << player_2.getBricksCounter();
	}
}

int Board::RunGame(int mode)
{
	srand(time(nullptr));
	int difficultyLevel=0;
	char key_1 = ' ', key_2 = ' ', key_flag = ' ';
	bool player2_isBomb = false, player1_isBomb = false, Player_1_played = false, newBrickOnTheScreen = false;
	bool player1_new_shape = true, player2_new_shape = true;
	int randomSmartMove = 0;
	int randRotation = rand(); // randomly rotate the brick when it borns (falls rotated)
	Point* currShape1 = player_1.getNewBrick()->getShape(); // getting shape
	Point* currShape2 = player_2.getNewBrick()->getShape(); // getting shape

	if (mode != HUMAN_VS_HUMAN)
	{
		difficultyLevel = difficulty();
	}

	Create_Print_Boards();	
	updateBricksCounter(0);
	updateBricksCounter(1);

	while (!ThereIsWinning())
	{	
		player1_isBomb = typeid(*(player_1.getMyBrick())) == typeid(Bomb);
		player2_isBomb = typeid(*(player_2.getMyBrick())) == typeid(Bomb);
		Player_1_played = false;

		if (mode == COPMUTER_VS_COMPUTER || mode == HUMAN_VS_COMPUTER)
		{
			randomSmartMove = getRandomInsertToComputedMove(difficultyLevel);
			if (mode == COPMUTER_VS_COMPUTER)
			{
				if (_kbhit())
					key_flag = _getch(); // get input from human, to give the oppertunity to press 'ESCAPE'

				if (player1_new_shape)
				{
					if (difficultyLevel == BEST || randomSmartMove)
					{
						computedMove(BOARD_1_START_INDEX, player_1.getMyBrick(), board);
					}
					else
					{
						updateGPSinRandomMove(BOARD_1_START_INDEX); // get random move, as difficulty is not 'best'
					}

					if (gps1.getY())
					{
						currShape1->setShapeInPosition(currShape1, NO_CHANGE_IN_SIDES, GO_DOWN_ONE_ROW);
					}

					player1_new_shape = false;
				}

				key_1 = decipherGPS(gps1, BOARD_1_START_INDEX); //get next move
				if (CheckMove1(currShape1, key_1))
					player_1.setDirection1(key_1);
			}

			if (player2_new_shape)
			{
				if (difficultyLevel == BEST || randomSmartMove)
					computedMove(BOARD_2_START_INDEX, player_2.getMyBrick(), board);
				else
					updateGPSinRandomMove(BOARD_2_START_INDEX); //get random move, as difficulty is not 'best'
				if (gps2.getY())
					currShape2->setShapeInPosition(currShape2, NO_CHANGE_IN_SIDES, GO_DOWN_ONE_ROW);
				player2_new_shape = false;
			}
			key_2 = decipherGPS(gps2, BOARD_2_START_INDEX); // get next move

			if (CheckMove2(currShape2, key_2))
				player_2.setDirection2(key_2);
		}
		if(mode!= COPMUTER_VS_COMPUTER)
		{
			if (_kbhit())
			{
				key_1 = _getch();
				Player_1_played = HandleHit1(currShape1, currShape2, key_1, mode);
			}
			if (_kbhit() && mode == HUMAN_VS_HUMAN)
			{
				key_2 = _getch();
				HandleHit2(currShape1, currShape2, key_2, Player_1_played);
			}
		}

		clearKeyboardBuffer(); //cleans the buffer

		if (key_1!=ESCAPE && key_2 != ESCAPE && key_flag!=ESCAPE )
		{
			if (NotBlockedFromBelow(currShape1))// no barrier from below - brick is allowed to go down one row
				player_1.getMyBrick()->DropBrick();
			else
			{
				player1_isBomb ? bombExplosion(*(player_1.getMyBrick()->getShape())) : updateBoard(currShape1);
				Brick* b1= player_1.getMyBrick();
				delete b1; //delete the dynamic allocation
				currShape1 = player_1.getNewBrick()->getShape(); // getting shape
				player1_new_shape = true;
				updateBricksCounter(0);
				player_1.getMyBrick()->setRotationZero(); // initializing rotations counter
				if (!(randRotation % RANDOM_SEQ))
				{
					currShape1->setShapeInPosition(currShape1, NO_CHANGE_IN_SIDES, GO_DOWN_ONE_ROW); //chekc if zigzag ok
					player_1.getMyBrick()->setBornRotation(BORNED_ROTATED);
					player_1.getMyBrick()->rotateClockWise(PLAY_MODE);// randomly rotate the brick when it borns (falls rotated)
				}
				randRotation = rand();
			}

			if (NotBlockedFromBelow(currShape2)) // no barrier from below - brick is allowed to go down one row
				player_2.getMyBrick()->DropBrick();
			else
			{
				player2_isBomb ? bombExplosion(*(player_2.getMyBrick()->getShape())) : updateBoard(currShape2); 
				Brick* b2 = player_2.getMyBrick();
				delete b2; //delete the dynamic allocation
				currShape2 = player_2.getNewBrick()->getShape(); // getting shape
				currShape2->setShapeInPosition(currShape2, (PLAYER_2_X_INIT_POINT- player_2.getMyBrick()->getMaxLeft()), NO_CHANGE_IN_LEVEL);
				player2_new_shape = true;
				updateBricksCounter(1);
				player_2.getMyBrick()->setRotationZero();// initializing rotations counter
				if (!(randRotation % RANDOM_SEQ))
				{
					currShape2->setShapeInPosition(currShape2, NO_CHANGE_IN_SIDES, GO_DOWN_ONE_ROW); //chekc if zigzag ok
					player_2.getMyBrick()->setBornRotation(BORNED_ROTATED);
					player_2.getMyBrick()->rotateClockWise(PLAY_MODE);// randomly rotate the brick when it borns (falls rotated)
				}
				randRotation = rand();
			}
		}
		else // KEY=ESC
		{
			int choose = menu(PAUSE);
			if (choose == RESUME_GAME) // resume game from where we stopped
			{
				key_1 = DOWN;
				key_2 = DOWN;
				key_flag = DOWN;
			}
			else if (choose == NEW_GAME) // returns back to main, and start a new game
				return choose;
			else
				return END_GAME; // returns back to main and exit game by main
		}
		checkForFullLines(); // checking if a row has been filled. if positive - clears the row, and updating score
		timePause(); // pauseing time
	}
	return WE_HAVE_A_WINNER; // we finished the loop - go back to main.
}


void Board::bombExplosion(Point coordinate)
{
	int leftborder = coordinate.getX() - 4;
	int rightborder = leftborder + 8;
	int roof = coordinate.getY() - 4;
	int floor = roof + 8;

	while ((rightborder > BOARD_1_END_PLAYING_INDEX && rightborder < BOARD_2_START_INDEX) || rightborder > BOARD_2_END_PLAYING_INDEX)
		rightborder--;
	while (leftborder < BOARD_1_START_PLAYING_INDEX || (leftborder > BOARD_1_END_INDEX && leftborder < BOARD_2_START_PLAYING_INDEX))
		leftborder++;
	while (roof < 1)
		roof++;
	while (floor >  BOARD_LENGTH-1)
		floor--;

	for (int i = roof; i < floor; i++)
		for (int j = leftborder; j <= rightborder; j++)
			board[i][j] = BLANK;

	board[coordinate.getY()][coordinate.getX()] = BLANK; //delete the bomb itself
	InitCureser();
	printBoard();
}


int  Board::ThereIsWinning()  // check if there is a winner
{
	for (int j = 1; j < BOARD_WIDTH - 2; j++)
	{
		if (board[LINE_ZERO][j] != BLANK && ( (j>BOARD_1_START_INDEX && j< BOARD_1_END_INDEX) || (j> BOARD_2_START_INDEX&& j< BOARD_2_END_INDEX)))
		{
			if (j < BOARD_1_END_INDEX)
			{
				winning(PLAYER_2);
				return WE_HAVE_A_WINNER;
			}
			else if (j > BOARD_2_START_INDEX)
			{
				winning(PLAYER1);
				return WE_HAVE_A_WINNER;
			}
		}
	}
	return NO_WINNER;
}

void  Board::winning(int player) const // announcing winner
{
	gotoxy(50, 6);
	cout << "PLAYER " << player << " IS THE WINNWER!!!";
	gotoxy(50, 8);
	cout << "PLEASE PRESS ESC TO CONTINUE";

	char ch = _getch();

	while (ch != ESCAPE)
	{
		ch = _getch();
		gotoxy(50, 6);

		if (player == PLAYER1)
			cout << "PLAYER 1 IS THE WINNWER!!!";
		else
			cout << "PLAYER 2 IS THE WINNWER!!!";
		
		gotoxy(50, 8);
		cout << "PLEASE PRESS ESC TO CONTINUE";
	}
}

bool Board::NotBlockedFromBelow(Point* shape) // return true if brick can no longer continue down
{	
	for (size_t i = 0; i < BRICK_SIZE; i++)
	{
		if (board[shape[i].getY() + 1][shape[i].getX()] != BLANK)
		{
			return BLOCKED;
		}
	}

	return UNBLOCKED;
}


bool Board::CheckMove1(Point* shape, char key) // return true if move is legal
{
	int operation = decode(key);

	if (operation == GO_TO_FLOOR_NOW)
		player_1.setDropLevel(checkPossibleLevel(shape)); 

	if ((operation == LEFT || operation == RIGHT) && !checkSides(shape, operation))
		return false;
	
	if (operation == ROTATION_CLOCK_WIZE)
		return checkRotation(shape, player_1.getMyBrick()->getRotationArray());

	if (operation == ROTATION_COUNTER_CLOCK_WIZE)
	{
		player_1.getMyBrick()->setRotationNumber(-1);
		bool res=checkRotation(shape, player_1.getMyBrick()->getRotationArray());
		if (res)
			return true;
		else
		{
			player_1.getMyBrick()->setRotationNumber(1);
			return false;
		}
	}

	return true;
}

bool Board::checkRotation(Point* shape, Point* deltas) // checks if rotation if possible (clockwise or counter clockwise)
{
	for (size_t i = 0; i < BRICK_SIZE; i++)
	{
		if (board[shape[i].getY() +deltas[i].getY() ][shape[i].getX() + deltas[i].getX()] != BLANK)
			return false;
	}

	return true;
}

bool Board::CheckMove2(Point* shape, char key) // return true if move is legal
{
	int operation = decode(key);

	if (operation == GO_TO_FLOOR_NOW)
		player_2.setDropLevel(checkPossibleLevel(shape));

	if ((operation==LEFT || operation==RIGHT) && !checkSides(shape, operation))
		return false;

	if (operation == ROTATION_CLOCK_WIZE)
		return checkRotation(shape, player_2.getMyBrick()->getRotationArray());

	if (operation == ROTATION_COUNTER_CLOCK_WIZE)
	{
		player_2.getMyBrick()->setRotationNumber(-1);

		bool res = checkRotation(shape, player_1.getMyBrick()->getRotationArray());
		if (res)
			return true;
		else
		{
			player_2.getMyBrick()->setRotationNumber(1);
			return false;
		}
	}

	return true;
}


int Board::checkPossibleLevel(Point* shape) const // return where the brick should be after choosing "drop"
{
	int tmp = BOARD_LENGTH;
	int min = BOARD_LENGTH;

	for (size_t i = 0; i < BRICK_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_LENGTH; j++)
		{
			if (board[j][shape[i].getX()] != BLANK)
				tmp = j - shape[i].getY()-1;
			if (min > tmp)
				min = tmp;
		}
	}

	return min;
}


int  Board::decode(char key) const // returns movement according to the choosen key key 
{
	if (key == 'a' || key == 'A' || key == 'J' || key == 'j')//left
		return LEFT;
	else if (key == 'd' || key == 'D' || key == 'l' || key == 'L')//right
		return RIGHT;
	else if (key == 'x' || key == 'X' || key == 'm' || key == 'M') // bomb
		return GO_TO_FLOOR_NOW;
	else if (key == 'S' || key == 's' || key == 'k' || key == 'K')
		return ROTATION_CLOCK_WIZE;
	else
		return ROTATION_COUNTER_CLOCK_WIZE;
}


bool Board::checkSides(Point* shape, int direction) // return true if moving aside is legal
{
	for (int i = 0; i < BRICK_SIZE; i++)
	{
		if(board[shape[i].getY()][shape[i].getX()+direction] != BLANK)
			return false;
	}

	return true;
}


void Board::updateBoard(Point* shape) // make the brick part of the board after it stopped
{
	for (int i = 0; i < BRICK_SIZE; i++)
	{
		board[shape[i].getY()][shape[i].getX()] = PLAYERS_FIGURE;
		gotoxy(shape[i].getX(), shape[i].getY());
		putchar(board[shape[i].getY()][shape[i].getX()]);
	}
}


bool Board::checkForFullLines() // checking if a row has been filled. if positive - clears the row, and updating score
{
	int counter = 0;
	bool Line_Status = NOT_DELETED;

	for (size_t i = 1; i <BOARD_LENGTH ; i++)
	{
		for (size_t j = 1; j < BOARD_1_WIDTH - 1; j++)
		{
			if (board[i][j] == PLAYERS_FIGURE)
			{
				counter++;
				if (counter == SIZE_OF_ROW)
				{
					DeleteRow(i,j);
					Line_Status = DELETED;
					player_1.setScore();
				}
			}
		}
		counter = 0;
	}

	for (size_t i = 1; i < BOARD_LENGTH; i++)
	{
		for (size_t j = BOARD_2_START_INDEX+1; j < BOARD_WIDTH - 1; j++)
		{
			if (board[i][j] == PLAYERS_FIGURE)
			{
				counter++;
				if (counter == SIZE_OF_ROW)
				{
					DeleteRow(i, j);
					Line_Status = DELETED;
					player_2.setScore();
				}
			}
		}
		counter = 0;
	}

	if (Line_Status)
	{
		InitCureser();
		printBoard();
	}

	return Line_Status;
}


void Board::DeleteRow(int i, int j) // deleting full row
{
	if (j < BOARD_1_WIDTH-1)
	{
		for (size_t j = 1; j < BOARD_1_WIDTH - 1; j++) // deleting the row
		{
			board[i][j] = BLANK;
			putchar(board[i][j]);
		}

		for (size_t k = i; k > 0; k--)
		{
			for (size_t r = 1; r < BOARD_1_WIDTH - 1; r++)
				board[k][r] = board[k - 1][r];
		}
	}

	if(j> BOARD_2_START_INDEX)
	{
		for (size_t j = BOARD_2_START_INDEX+1; j < BOARD_WIDTH-1; j++) // deleting the row
		{
			board[i][j] = BLANK;
			putchar(board[i][j]);
		}

		for (size_t k = i; k > 0; k--)
		{
			for (size_t r = BOARD_2_START_INDEX+1; r < BOARD_WIDTH - 1; r++)
				board[k][r] = board[k - 1][r];
		}
	}
}

int Board::gameMode() const
{
	char choose = ' ';

	cls();
	cout << "Choose game mode:" << endl << endl;
	cout << "For Human vs Human - press (1)\n" <<
		"For Human vs Computer - press (2)\nFor Comuter vs Computer- press (3)" << endl;

	while (choose != 1 && choose != 2 && choose != 3)
	{
		choose = _getch();
		// loop that will show the menu
		switch (choose)
		{
		case('1'):
			return HUMAN_VS_HUMAN;
		case('2'):
			return HUMAN_VS_COMPUTER;
		case('3'):
			return COPMUTER_VS_COMPUTER;
		}
	}
}


int  Board::menu(int reason)  // game menu
{
	int mode = 0;
	char choose = ' ';
	if (reason == NEW_GAME)
		sayHello();
	else //reason is PAUSE
		pauseMessage();

	while (choose != 1 && choose != 2 && choose != 8 && choose != 9)
	{
		choose = _getch();
		// loop that will show the menu
		switch (choose)
		{
		case('1'):
			if (reason != PAUSE)
			{
				mode = gameMode();
				return mode;
			}
			return NEW_GAME;
		case('2'):
			cls();
			printBoard();
			return RESUME_GAME;
		case('8'):
			cls();//clear screen
			printInstructionAndKeys();
			if (reason == PAUSE)
				pauseMessage();
			else
				cout << "For a new game - press (1)\n" <<"For Tetris instructions and keys - press (8)\nFor exit- press (9)" << endl;
			break;
		case ('9'):
			endGame();
			return END_GAME;
		}
	}
}


void  Board::endGame() const // end game output for user
{
	cls();
	gotoxy(50, 8);
	cout << "GOODBYE!";
	Sleep(1000);
	cls();
}

void Board::initBoard() // initializing board with: ' '
{
	for (size_t i = 0; i < BOARD_LENGTH; i++)
	{
		for (size_t j = 0; j < BOARD_WIDTH; j++)
			board[i][j] = BLANK;
	}
}

void  Board::Printscore()  const // printing the score
{
	gotoxy(COLUMN_ZERO, BOARD_LENGTH + 2);
	cout << "PLAYER 1 SCORE: " << player_1.getScore();

	gotoxy(OFFSET_BOARD_1_2 -1, BOARD_LENGTH+2);
	cout << "PLAYER 2 SCORE: " << player_2.getScore();
}

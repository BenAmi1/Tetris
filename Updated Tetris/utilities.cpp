#include "utilities.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void hideCurser()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void cls()
{
	system("cls");
}

void clearKeyboardBuffer()
{
	char junk;
	while (_kbhit())
	{
		junk = _getch();
	}
}

void printInstructionAndKeys() // instruction of Tetris
{
	char choose = ' ';
	cout << "The aim in Tetris is simple; you bring down blocks from the top of the screen.\n\
You can move the blocks around, either left to right and/or you can rotate them.\n\
The blocks fall at a certain rate, but you can make them fall faster if you’re sure of your positioning.\n\
Your objective is to get all the blocks to fill all the empty space in a line at the bottom of the screen. \n\
whenever you do this, you will find that the blocks vanish and you get awarded some points." << endl << endl;

	cout << "Keys for player 1: (Left board) \n A-Left\n D-Right\n W-Rotate counter clockwise\n S-Rotate clockwise\n X-Drop\n " << endl;
	cout << "Keys for player 2: (Right board) \n J-Left\nL-Right\n I-Rotate counter clockwise\n K-Rotate clockwise\n M-Drop\n " << endl << endl;
	cout << "In case of Bomb, there will be an explosion of 9X9 figures in the board\n\n";
	

	cout << "Game platform supports lower / upper case keys" << endl << endl;

	cout << "Press (b) to go back to main menu, or (0) to exit" << endl;
	choose = _getch();

	while (choose != 'b' && choose != 'B' && choose != '0')
	{
		cls();
		cout << "Wrong key was pressed, please Press (b) to go back to main menu, or (0) to exit " << endl << endl;
		choose = _getch();
	}

	switch (choose)
	{
	case('b'):
		cls();
		return; 
	case('B'):
		cls();
		return; 
	case('0'):
		exit(END_GAME);
		break;
	}
}

void sayHello()
{
	cout << "Hello! welcome to Tetris!" << endl << endl;
	cout << "For a new game - press (1)\n" <<
		"For Tetris instructions and keys - press (8)\nFor exit- press (9)" << endl;
}

void pauseMessage()
{
	cls();
	cout << "For a new game - press (1)\n" <<
		"To resume current game - press(2)\nFor Tetris instructions and keys - press (8)\nFor exit- press (9)" << endl;
}

void InitCureser()
{
	gotoxy(0, 0);
}
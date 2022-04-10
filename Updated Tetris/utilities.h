#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include <wingdi.h>
#include <stdlib.h>
#include <time.h>

using::std::cout;
using::std::endl;

#define OFFSET_BOARD_1_2 25 
#define BLANK ' '
#define LINE_ZERO 0
#define PLAYER_1_X_INIT_POINT 6
#define PLAYER_2_X_INIT_POINT  (OFFSET_BOARD_1_2 + PLAYER_1_X_INIT_POINT -1)
#define PLAYERS_Y_INIT_POINT 0
#define BOARD_LENGTH 20
#define BOARD_WIDTH 38
#define BOARD_FIGURE 219
#define NUM_OF_VALID_KEYS 5
#define LEFT -1
#define RIGHT 1
#define DOWN 't'
#define ROTATE 0
#define DEFAULT_VALUE 0
#define BOARD_HEIGHT 12
#define BRICK_SIZE 4
#define BLOCKED false
#define UNBLOCKED true
#define BOARD_1_WIDTH 14
#define COLUMN_ZERO 0
#define BOARD_2_START_INDEX OFFSET_BOARD_1_2-1
#define BOARD_2_END_INDEX BOARD_2_START_INDEX+13
#define BOARD_1_START_INDEX 0
#define BOARD_1_END_INDEX 13
#define PLAYERS_FIGURE '$'
#define GO_TO_FLOOR_NOW 2
#define ROTATION 3
#define DELETED true
#define NOT_DELETED false
#define WE_HAVE_A_WINNER 4
#define NO_WINNER false
#define EXIT_OUTPUT 25
#define SIZE_OF_ROW 12
#define NEW_GAME 1
#define CONTINUE_GAME true
#define gameOn 1
#define ESCAPE 27
#define END_GAME 0
#define RESUME_GAME 2
#define END_GAME 0
#define ROTATION_CLOCK_WIZE 4
#define ROTATION_COUNTER_CLOCK_WIZE 5
#define PAUSE 2
#define WINNER 1
#define EXIT_GAME 0
#define BORNED_ROTATED 1
#define ROTATED_BY_PLAYER 0
#define BEST 0
#define GOOD 1
#define NOVICE 2
#define PLAYER1 1
#define PLAYER_2 2
#define TIME_PAUSE 350
#define RANDOM_SEQ 5
#define BOMB_SIZE 1
#define HUMAN_VS_HUMAN 1
#define HUMAN_VS_COMPUTER 8
#define COPMUTER_VS_COMPUTER 9
#define PLAY_MODE 0
#define TEST_MODE 1
#define BOARD_1_END_PLAYING_INDEX 12
#define BOARD_1_START_PLAYING_INDEX 1
#define BOARD_2_END_PLAYING_INDEX 36
#define BOARD_2_START_PLAYING_INDEX 25
#define LAST_ROTATION_ITERATION 3
#define NO_CHANGE_IN_SIDES 0
#define GO_DOWN_ONE_ROW 1 
#define NO_CHANGE_IN_LEVEL 0
#define DEFAULT_X_PLAYER_1 1
#define DEFAULT_X_PLAYER_2 25
#define BOMB_RANGE_ONE_SIDE 4
#define NUBMER_OF_BRICK_TYPES 7
#define BOMB_APPEARENCE_PROBABILITY 20
#define FIRST_ITERATION 0
#define RANDOM_ROTATION 3
#define RANDOM_HORIZONAL_MOVE 6
#define RANDOM_LEFT_OR_RIGHT 2
#define DEFAULT_VALUE 0

void gotoxy(int x, int y);
void hideCurser(); // hiding curser
void cls(); // clear screen
void clearKeyboardBuffer(); // cleans the buffer
void printInstructionAndKeys();
void sayHello();
void pauseMessage();
void InitCureser();

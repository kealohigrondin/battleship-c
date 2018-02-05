#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10
#define WATER '~'
#define CARRIER 'C'
#define BATTLESHIP 'B'
#define SUBMARINE 'S'
#define DESTROYER 'D'
#define PATROLBOAT 'P'
#define CARR_L 5
#define BATL_L 4
#define SUBM_L 3
#define DSTR_L 3
#define PABO_L 2
#define AUTO 1
#define MANUAL 0
#define HIT '*'
#define MISS 'm'
#define PLAYER "PLAYER 1"
#define CPU "CPU"

typedef struct cell
{
	int row;
	int col;
	char type;
}Cell;
typedef struct ship
{
	int originRow;
	int originCol;
	char direction;
	char shipType;
	int shipLength;
}Ship;
typedef enum bool
{
	TRUE, FALSE
}Bool;
typedef struct stats
{
	int misses;
	int hits;
	int hitPercent;
}Stats;

//Menu methods
void initBoard(Cell board[][COLS], int rows, int cols);
void printBoard(Cell board[][COLS], int rows, int cols);
void welcomeScreen(Cell board[][COLS]);
void printRules();
void evalOption(char option, Cell board[][COLS]);

//Board initialization methods
void manOrAuto(Cell board[][COLS]);
void manualShipAssign(Cell board[][COLS]);
void autoShipAssign(Cell board[][COLS]);
void validateOrigin(Cell board[][COLS], Ship tempship, int assignType);
void validateDir(Cell board[][COLS], Ship tempship, int assignType);
void validateShip(Cell board[][COLS], Ship tempship, int assignType);
Bool checkDir(Cell board[][COLS], Ship shippy);
void placeShip(Ship shippy, Cell board[][COLS]);
Bool checkOrigin(Cell board[][COLS], Ship tempship);
void getCoorMan(Cell board[][COLS], int shipLength);
void getCoorAuto(Cell board[][COLS], int shipLength);
void getNewDirMan(char* dir);

//Gameplay methods
void takeGuess(int* pXGuess, int* pYGuess);
char checkGuess(Cell board[][COLS], int xGuess, int yGuess, char* pShipType);
void updateBoard(Cell board[][COLS], int x, int y, char HorM);
void autoGuess(int* pX, int* pY);
int checkEndGame(Cell p1board[][COLS], Cell cpuboard[][COLS]);
void updateShipStatus(char shipType, int shipStatus[]);
void checkSunkShip(char shipType, int shipStatus[], char player[], FILE* outfile);
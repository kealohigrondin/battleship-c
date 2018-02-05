/*
Kealohi Grondin
PA 6- Battleship
November 6, 2017
credit to user gabrieledcjr on github
rules taken from the assignment page
*/
#include "battleship.h"

int main(void)
{
	int p1ShipStatus[5] = { 5, 4, 3, 3, 2 }, cpuShipStatus[5] = { 5, 4, 3, 3, 2 };
	Stats p1Stats = { {0}, {0}, {0} }, cpuStats = {{ 0 }, { 0 }, { 0 }};
	Bool validGuess = FALSE;
	int checker = -1, roundcounter = 1, p1HitCounter = 0, p1MissCounter = 0,
		cpuHitCounter = 0, cpuMissCounter = 0, xGuess = 0, yGuess = 0,
		*pXGuess = &xGuess, *pYGuess = &yGuess;
	char hitOrMiss = '\0', shipType = '\0', *pShipType = &shipType;
	FILE* outFile = fopen("battleship.log", "w");

	//initializes game boards
	Cell p1board[ROWS][COLS], cpuboard[ROWS][COLS], p1Guesses[ROWS][COLS];
	initBoard(p1board, ROWS, COLS);
	initBoard(cpuboard, ROWS, COLS);
	initBoard(p1Guesses, ROWS, COLS);

	//assigns ships to all game boards
	autoShipAssign(cpuboard);
	welcomeScreen(p1board);
	printf("\nYOUR BOARD:");
	printBoard(p1board, ROWS, COLS);

	printf("\nCPU BOARD:");
	printBoard(cpuboard, ROWS, COLS);

	while (checker != 0 && checker != 1)
	{
		fprintf(outFile, "ROUND %d: \n", roundcounter);
		//player 1 turn
		takeGuess(pXGuess, pYGuess);	//takes in player guess
		fprintf(outFile, "Player turn: (%d,%d) ", xGuess, yGuess);
		hitOrMiss = checkGuess(cpuboard, xGuess, yGuess, pShipType);//checks if its a hit or miss
		switch (hitOrMiss)			//tells player if they got a hit or miss
		{
		case HIT:
			printf("\n\n\nYOU HIT A CPU SHIP");
			fprintf(outFile, "HIT\n");
			updateShipStatus(shipType, cpuShipStatus);
			checkSunkShip(shipType, cpuShipStatus, PLAYER, outFile);
			p1Stats.hits++;
			break;
		case MISS:
			printf("\n\n\nYOU MISSED");
			fprintf(outFile, "MISS\n");
			p1Stats.misses++;
			break;
		}
		updateBoard(p1Guesses, xGuess, yGuess, hitOrMiss);	//updates players view of cpu board

		//cpu turn
		autoGuess(pXGuess, pYGuess);
		fprintf(outFile, "CPU turn: (%d,%d) ", xGuess, yGuess);
		hitOrMiss = checkGuess(p1board, xGuess, yGuess, pShipType);
		switch (hitOrMiss)	//tells player if CPU got a hit or miss
		{
		case HIT:
			printf("\n\n\n CPU HIT ONE OF YOUR SHIPS");
			fprintf(outFile, "HIT\n\n");
			updateShipStatus(shipType, cpuShipStatus);
			checkSunkShip(shipType, cpuShipStatus, CPU, outFile);
			cpuStats.hits++;
			break;
		case MISS:
			printf("\n\n\nCPU MISSED");
			fprintf(outFile, "MISS\n\n");
			cpuStats.misses++;
			break;
		}
		updateBoard(p1board, xGuess, yGuess, hitOrMiss);
		printf("\nYOUR BOARD:");
		printBoard(p1board, ROWS, COLS);
		printf("\nYOUR GUESSES:");
		printBoard(p1Guesses, ROWS, COLS);
		checker = checkEndGame(p1Guesses, p1board);//-1 if not over, 0 if cpu win, 1 if p1 win
		roundcounter++;
	}
	switch (checker)
	{
	case 0:
		printf("\n\n\n\n\n\nMACHINE BEAT YOU- YOU LOSE\n");
		fprintf(outFile, "CPU WINS, PLAYER LOSES\n\n");
		break;
	case 1:
		printf("\n\n\n\n\n\nMAN BEAT MACHINE- YOU WIN\n");
		fprintf(outFile, "PLAYER WINS, CPU LOSES\n\n");
		break;
	}
	p1Stats.hitPercent = (p1Stats.hits / (p1Stats.hits + p1Stats.misses)) * 100;
	cpuStats.hitPercent = (cpuStats.hits / (cpuStats.hits + cpuStats.misses)) * 100;

	fprintf(outFile, "\n\nTOTAL ROUNDS PLAYED: %d\n\n===PLAYER STATS===\nTotal Hits: %d\n"
		"Total Misses: %d\nHit %%: %d%%",
		roundcounter, p1Stats.hits, p1Stats.misses, p1Stats.hitPercent);
	fprintf(outFile, "\n\n===CPU STATS===\nTotal Hits: %d\n"
		"Total Misses: %d\nHit %%: %d%%",
		cpuStats.hits, cpuStats.misses, cpuStats.hitPercent);
	fclose(outFile);
}
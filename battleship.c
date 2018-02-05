#include "battleship.h"

/*
Method Name: initBoard
Purpose: initialize game board to water, '~'
*/
void initBoard(Cell board[][COLS], int rows, int cols)
{
	for (int r = 0; r < rows; r++)//goes through rows
	{
		for (int c = 0; c < cols; c++)//goes through columns
		{
			board[r][c].row = r;
			board[r][c].col = c;
			board[r][c].type = WATER;	//sets cell to '~'
		}
	}
}


/*
Method Name: printBoard
Purpose: To print the game board that is passed to it
*/
void printBoard(Cell board[][COLS], int rows, int cols)
{
	printf("\n\n   ");//spacing
	for (int i = 0; i < rows; i++)
	{
		printf("%d ", i);
	}
	putchar('\n');
	for (int r = 0; r < rows; r++)//goes through rows
	{
		printf("%d  ", r);
		for (int c = 0; c < cols; c++)//goes through columns
		{
			printf("%c ", board[r][c].type);	//prints cell
		}
		putchar('\n');//prints newline
	}
}


/*
Method Name: welcomeScreen
Purpose: To print the starting screen and determine what the user wants to do
		(look at rules or start the game)
*/
void welcomeScreen(Cell board[][COLS])
{
	char option = '\0';
	printf("=====WELCOME TO BATTLESHIP=====\n\n"
		"This is a two player game, you're playing against the computer.\n"
		"Enter \'r\' if you want to view the rules, otherwise enter \'s\' to start the game\n\n");
	scanf(" %c", &option);
	evalOption(option, board);
}


/*
Method Name: printRules
Purpose: To print the rules of the game
*/
void printRules()
{
	printf("\n\n\nRULES\n\n\n"
		"Battleship is a two player Navy game. The objective of the game is to sink all ships in your\n"
		"enemy's fleet. The Player to sink his/her enemy's fleet first wins. Both players' fleets\n"
		"consist of 5 ships that are hidden from the enemy. Each ship may be differentiated by its size\n"
		"(besides the Destroyer and Submarine) or number of cells it expands on the game board. The\n"
		"Carrier has 5 cells, Battleship has 4 cells, Destroyer and Submarine have 3 cells each, and\n"
		"the Patrol Boat has 2 cells.\n\n\n");
}


/*
Method Name: evalOption
Purpose: To evaluate the input from the user of what they want to do- 
		read rules or start the game
*/
void evalOption(char option, Cell board[][COLS])
{
	switch (option)
	{
	case 'r':
	case 'R':
		printRules();
		welcomeScreen(board);
		break;
	case 's':
	case 'S':
		manOrAuto(board);
		break;
	default:
		printf("ERROR");
		welcomeScreen(board);
		break;
	}
}


/*
Method Name: manOrAuto
Purpose: Prompts user to choose manual or automatic ship assignment to the board
*/
void manOrAuto(Cell board[][COLS]) 
{ 
	int option = -1;
	printf("Choose one option:\n1. Manually assign ship spots\n2. Automatically assign ship spots\n");
	scanf("%d", &option);
	switch (option)
	{
	case 1: manualShipAssign(board);
		break;
	case 2: autoShipAssign(board);
		break;
	default: printf("\n\nERROR INVALID INPUT\n\n\n");
		manOrAuto(board);
	}
}


/*
Method Name: manualShipAssign
Purpose: manually assigns the ship positions based on user input for all the ships
*/
void manualShipAssign(Cell board[][COLS])
{
	for (int i = 0; i < 5; i++)
	{
		getCoorMan(board, i);
	}
}


/*
Method Name: autoShipAssign
Purpose: automatically assigns ships to the game board
*/
void autoShipAssign(Cell board[][COLS]) 
{
	for (int i = 0; i < 5; i++)
	{
		getCoorAuto(board, i);
	}
}


/*
Method Name: getCoorMan
Purpose: To manually get the origin coordinates and ship direction for a ship from the user
		then passes that information to validateShip
*/
void getCoorMan(Cell board[][COLS], int shipLength)
{
	Ship tempship, *pTempship = &tempship;
	Bool validDir = FALSE, validOrigin = FALSE;
	switch (shipLength)
	{
	case 0:
		printf("Enter origin point for the CARRIER (ship length: 5): ");
		tempship.shipType = CARRIER;
		tempship.shipLength = CARR_L;
		break;
	case 1:
		printf("Enter origin point for the BATTLESHIP (4): ");
		tempship.shipType = BATTLESHIP;
		tempship.shipLength = BATL_L;
		break;
	case 2:
		printf("Enter origin point for the SUBMARINE (3): ");
		tempship.shipType = SUBMARINE;
		tempship.shipLength = SUBM_L;
		break;
	case 3:
		printf("Enter origin point for the DESTROYER (3): ");
		tempship.shipType = DESTROYER;
		tempship.shipLength = DSTR_L;
		break;
	case 4:
		printf("Enter origin point for the PATROL BOAT (2): ");
		tempship.shipType = PATROLBOAT;
		tempship.shipLength = PABO_L;
		break;
	}

	//GETS ORIGIN
	scanf("%d %d", &tempship.originRow, &tempship.originCol);
	validOrigin = checkOrigin(board, tempship);	//checks for valid origin
	while (validOrigin != TRUE)	//gets new origin if invalid until there is a valid origin
	{
		printf("\n\n\nERROR: INVALID SHIP ORIGIN\n\nENTER NEW SHIP ORIGIN: ");
		scanf(" %d %d", &tempship.originRow, &tempship.originCol);
		validOrigin = checkOrigin(board, tempship);
	}


	//GETS DIRECTION
	printf("Enter direction you want ship to point from the origin (u, d, l, r)");
	scanf(" %c", &tempship.direction);
	validDir = checkDir(board, tempship);	//checks for valid direction
	while (validDir != TRUE)
	{
		getNewDirMan(&tempship.direction);
		validDir = checkDir(board, tempship);
	}
	placeShip(tempship, board);
}


/*
Method Name: getCoorAuto
Purpose: automatically gets the origin coordinates and direction for a ship
		then passes that information to validateShip
*/
void getCoorAuto(Cell board[][COLS], int shipLength)
{
	Ship tempship;
	srand((unsigned int)time(NULL));

	//creates an array of directions for random direction selection
	char randDirection[4] = { 'u', 'd', 'l', 'r' };

	//randomly generates origin row, column, and direction
	tempship.originRow = rand() % 10;
	tempship.originCol = rand() % 10;
	tempship.direction = randDirection[rand() % 4];

	//generates ship type and length based on the iteration in the the for loop in getCoorAuto 
	switch (shipLength)
	{
	case 0:
		tempship.shipType = CARRIER;
		tempship.shipLength = CARR_L;
		break;
	case 1:
		tempship.shipType = BATTLESHIP;
		tempship.shipLength = BATL_L;
		break;
	case 2:
		tempship.shipType = SUBMARINE;
		tempship.shipLength = SUBM_L;
		break;
	case 3:
		tempship.shipType = DESTROYER;
		tempship.shipLength = DSTR_L;
		break;
	case 4:
		tempship.shipType = PATROLBOAT;
		tempship.shipLength = PABO_L;
		break;
	}
	validateShip(board, tempship, AUTO);
}


/*
Method Name: validateShip
Purpose: to validate the origin and direction of the ship. If one of them is invalid, 
		it will get a new one until it is valid
Input: the board, a ship to be placed, and the type of assignment it is (auto or manual)
*/
void validateShip(Cell board[][COLS], Ship tempship, int assignType)
{
	Bool validOrigin = FALSE;

	//checks for valid origin, dont take out
	validOrigin = checkOrigin(board, tempship);

	//gets new origin if invalid until there is a valid origin
	while (validOrigin != TRUE)
	{
		if (assignType == MANUAL)
		{
			printf("\n\n\nERROR: INVALID SHIP ORIGIN\n\nENTER NEW SHIP ORIGIN: ");
			scanf(" %d %d", &tempship.originRow, &tempship.originCol);
		}
		else  //assigns new rand origin
		{
			tempship.originRow = rand() % 10;
			tempship.originCol = rand() % 10;
		}
		validOrigin = checkOrigin(board, tempship);
	}

	Bool validDir = FALSE;

	//checks for valid direction, dont take out
	validDir = checkDir(board, tempship);

	while (validDir != TRUE)
	{
		if (assignType == MANUAL)
		{
			char* dir = &tempship.direction;
			getNewDirMan(dir);
		}
		else
		{
			char randDir[4] = { 'u', 'd', 'l', 'r' };
			tempship.direction = randDir[rand() % 4];
		}
		validDir = checkDir(board, tempship);
	}
	placeShip(tempship, board);
}


/*
Method Name: validateDir
Purpose: To validate the direction of the ship. If the direction is invalid,
		a new direction is generated until it is valid
*/
void validateDir(Cell board[][COLS], Ship tempship, int assignType)
{
	Bool validDir = FALSE;

	//checks for valid direction, dont take out
	validDir = checkDir(board, tempship);

	while (validDir != TRUE)
	{
		if (assignType == MANUAL)
		{
			char* dir = &tempship.direction;
			getNewDirMan(dir);
		}
		else
		{
			char randDir[4] = { 'u', 'd', 'l', 'r' };
			tempship.direction = randDir[rand() % 4];
		}
		validDir = checkDir(board, tempship);
	}
}


//ADD MORE TO CHECK WATER CELLS
/*
Method Name: checkDir
Purpose: checks the validity of the direction based on the ship length and origin
*/
Bool checkDir(Cell board[][COLS], Ship shippy)
{
	Bool validity = FALSE; 
	switch (shippy.direction)
	{
	case 'u':
	case 'U':
		for (int i = shippy.originRow; i >= shippy.shipLength - 1; i--)
		{
			if (board[i][shippy.originCol].type != WATER)
			{
				validity = FALSE;
				break;
			}
			else
				validity = TRUE;
		}
		break;
	case 'd':
	case 'D':
		for (int i = shippy.originRow; i < shippy.originRow + shippy.shipLength; i++)
		{
			if (board[i][shippy.originCol].type != WATER)
			{
				validity = FALSE;
				break;
			}
			else
				validity = TRUE;
		}
		break;
	case 'l':
	case 'L':
		for (int i = shippy.originCol; i >= shippy.shipLength - 1; i--)
		{
			if (board[shippy.originRow][i].type != WATER)
			{
				validity = FALSE;
				break;
			}
			else
				validity = TRUE;
		}
		break;
	case 'r':
	case 'R':
		for (int i = shippy.originCol; i <= 10 - shippy.shipLength; i++)
		{
			if (board[shippy.originRow][i].type != WATER)
			{
				validity = FALSE;
				break;
			}
			else
				validity = TRUE;
		}
		break;
	default:
		validity = FALSE;
	}//end switch
	return validity;
}


/*
Method Name: validateOrigin
Purpose: To validate the origin of the ship. If the origin is invalid,
		a new origin is generated until it is valid
*/
void validateOrigin(Cell board[][COLS], Ship tempship, int assignType)
{
	Bool validOrigin = FALSE;

	//checks for valid origin, dont take out
	validOrigin = checkOrigin(board, tempship);

	//gets new origin if invalid until there is a valid origin
	while (validOrigin != TRUE)
	{
		if (assignType == MANUAL)
		{
			printf("\n\n\nERROR: INVALID SHIP ORIGIN\n\nENTER NEW SHIP ORIGIN: ");
			scanf(" %d %d", &tempship.originRow, &tempship.originCol);
		}
		else  //assigns new rand origin
		{
			tempship.originRow = rand() % 10;
			tempship.originCol = rand() % 10;
		}
		validOrigin = checkOrigin(board, tempship);
	}
}


/*
Method Name: checkOrigin
Purpose: checks the validity of the origin based on if there is a ship in that spot already
*/
Bool checkOrigin(Cell board[][COLS], Ship shippy)
{
	Bool check;
	if (board[shippy.originRow][shippy.originCol].type != WATER)
		check = FALSE;
	else
		check = TRUE;
	return check;
}


/*
Method Name: placeShip
Purpose: to place the ship on the game board based on the ship, origin, and direction
*/
void placeShip(Ship shippy, Cell board[][COLS])
{
	switch (shippy.direction)
	{
	case 'u':
	case 'U':
		for (int r = shippy.originRow; r > shippy.originRow - shippy.shipLength; r--)
		{
			board[r][shippy.originCol].type = shippy.shipType;
		}
		break;
	case 'd':
	case 'D':
		for (int r = shippy.originRow; r < shippy.originRow + shippy.shipLength; r++)
		{
			board[r][shippy.originCol].type = shippy.shipType;
		}
		break;
	case 'l':
	case 'L':
		for (int c = shippy.originCol; c > shippy.originCol - shippy.shipLength; c--)
		{
			board[shippy.originRow][c].type = shippy.shipType;
		}
		break;
	case 'r':
	case 'R':
		for (int c = shippy.originCol; c < shippy.originCol + shippy.shipLength; c++)
		{
			board[shippy.originRow][c].type = shippy.shipType;
		}
		break;
	default:
		printf("Sum-Ting Wong in placeShip()");
	}
}

/*
Method Name: getNewDirMan
Purpose: gets a new direction for the ship from the user
*/
void getNewDirMan(char* dir)
{
	printf("\n\nERROR: INVALID SHIP DIRECTION\n\nENTER NEW SHIP DIRECTION (u, d, l, r): ");
	scanf(" %c", dir);
}



/*
Method Name: takeGuess
Purpose: ask the user to guess (x,y) coordinates of where a cpu ship is
*/
void takeGuess(int* pXGuess, int* pYGuess)
{
	printf("Enter guess (row,col) of where a cpu ship is: ");
	scanf("%d %d", pXGuess, pYGuess);
}


/*
Method Name: checkGuess
Purpose: verify that the guessed coordinates are valid
*/
char checkGuess(Cell board[][COLS], int xGuess, int yGuess, char* pShipType)
{
	*pShipType = board[xGuess][yGuess].type;
	char update = '\0';
	if (board[xGuess][yGuess].type == CARRIER || board[xGuess][yGuess].type == BATTLESHIP || 
		board[xGuess][yGuess].type == DESTROYER || board[xGuess][yGuess].type == SUBMARINE || 
		board[xGuess][yGuess].type == PATROLBOAT)
	{
		update = HIT;
	}
	else if (board[xGuess][yGuess].type == WATER)
	{
		update = MISS;
	}
	else if (board[xGuess][yGuess].type == HIT ||
			 board[xGuess][yGuess].type == MISS)
		printf("\n\n\nYou already guessed this coordinate\n\n\n");
	else
		printf("\n\n\nERROR IN CHECKGUESS\n\n\n");
	return update;
}


/*
Method Name: updateBoard
Purpose: To update the board based on the user or cpu's guess
*/
void updateBoard(Cell board[][COLS], int x, int y, char HorM)
{
	board[x][y].type = HorM;
}


/*
Method Name: autoGuess
Purpose: To guess coordinates for the computer
*/
void autoGuess(int* pX, int* pY)
{
	srand((unsigned int)time(NULL));
	*pX = rand() % 10;
	*pY = rand() % 10;
}


/*
Method Name: checkEndGame
Purpose: To check if the player or cpu has won

returns -1 if the game isn't over, 0 if the cpu won, or 1 if p1 won
*/
int checkEndGame(Cell p1Guesses[][COLS], Cell cpuGuesses[][COLS])
{
	int cpuNumHits = 0, p1NumHits = 0, endgame = -1;
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (p1Guesses[r][c].type == HIT)
				p1NumHits++;
			if (cpuGuesses[r][c].type == HIT)
				cpuNumHits++;
		}
	}
	if (p1NumHits == 17)//cpu wins
		endgame = 1;
	else if (cpuNumHits == 17)//p1 wins
		endgame = 0;
	return endgame;
}


/*
Method Name: updateShipStatus
Purpose: to update the remaining number of unscathed ship parts
*/
void updateShipStatus(char shipType, int shipStatus[])
{
	switch (shipType)
	{
	case CARRIER:
		shipStatus[0]--;
		break;
	case BATTLESHIP:
		shipStatus[1]--;
		break;
	case SUBMARINE:
		shipStatus[2]--;
		break;
	case DESTROYER:
		shipStatus[3]--;
		break;
	case PATROLBOAT:
		shipStatus[4]--;
		break;
	}
}


/*
Method Name: checkSunkShip
Purpose: To check if a ship has sunk, if so it tells the player what ship has sunk
*/
void checkSunkShip(char shipType, int shipStatus[], char player[], FILE* outfile)
{
	putchar('\n');
	switch (shipType)
	{
	case CARRIER:
		if (shipStatus[0] == 0)
		{
			printf("%s SUNK A CARRIER", player);
			fprintf(outfile, "%s SUNK A CARRIER\n", player);
		}			
		break;
	case BATTLESHIP:
		if (shipStatus[1] == 0)
		{
			printf("%s SUNK A BATTLESHIP", player);
			fprintf(outfile, "%s SUNK A BATTLESHIP\n", player);
		}
		break;
	case SUBMARINE:
		if (shipStatus[2] == 0)
		{
			printf("%s SUNK A SUBMARINE", player);
			fprintf(outfile, "%s SUNK A SUBMARINE\n", player);
		}
		break;
	case DESTROYER:
		if (shipStatus[3] == 0)
		{
			printf("%s SUNK A DESTROYER", player);
			fprintf(outfile, "%s SUNK A DESTROYER\n", player);
		}
		break;
	case PATROLBOAT:
		if (shipStatus[4] == 0)
		{
			printf("%s SUNK A PATROL BOAT", player);
			fprintf(outfile, "%s SUNK A PATROL BOAT\n", player);
		}
		break;
	}
}



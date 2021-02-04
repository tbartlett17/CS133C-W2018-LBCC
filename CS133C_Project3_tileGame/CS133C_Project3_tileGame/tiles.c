//********************************************************************************************
// Author: Tyler Bartlett
// File: tiles.c
// Date: 02/15/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 3
// Desc: mimics the vintage Sliding Tiles game
// Notes:
// 	this would be much better if implemented for wasd input to move the empty tile.
//		
//********************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // used for srand(time(null))

#define ROWS 4
#define COLUMNS 4
#define RNG_MAX_VAL 4
#define WIN_CON 15
#define SWAP_TOT 500 //how many times to swap elements of playerBoard matrix. more swaps means more random board

struct matrixCoordinates { int x1, x2, y1, y2; };

void swiperNoSwiping(char *matrix[4][4], struct matrixCoordinates matrixCoords)
{
	char *tempMatrix[ROWS][COLUMNS];
 	tempMatrix[matrixCoords.x1][matrixCoords.y1] = matrix[matrixCoords.x1][matrixCoords.y1];
	matrix[matrixCoords.x1][matrixCoords.y1] = matrix[matrixCoords.x2][matrixCoords.y2];
	matrix[matrixCoords.x2][matrixCoords.y2] = tempMatrix[matrixCoords.x1][matrixCoords.y1];
}

void boardRandomizer(char *matrix[4][4])
{
	struct matrixCoordinates matrixCoords;
	srand(time(NULL)); // something about seeding. this makes me generate different rand #s each run
	for (int swapCount = 0; swapCount < SWAP_TOT; swapCount++)
	{
		matrixCoords.x1 = rand() % RNG_MAX_VAL;
		matrixCoords.y1 = rand() % RNG_MAX_VAL;
		matrixCoords.x2 = rand() % RNG_MAX_VAL;
		matrixCoords.y2 = rand() % RNG_MAX_VAL;

		while (matrixCoords.x1 == matrixCoords.x2 && matrixCoords.y1 == matrixCoords.y2)
		{
			matrixCoords.x2 = rand() % RNG_MAX_VAL;
			matrixCoords.y2 = rand() % RNG_MAX_VAL;
		}
		swiperNoSwiping(matrix, matrixCoords);
	}
}

void boardPrinter(char *matrix[4][4])
{
	printf(" -------------------------\n");
	for (int j = 0; j<COLUMNS; j++)
	{
		printf("| ");
		for (int i = 0; i<ROWS; i++)
		{
			if (i == ROWS-1)
			{
				printf("%s |", matrix[j][i]);
			}
			else
			{
				printf("%s\t", matrix[j][i]);
			}
		}
		printf("\n");
	}
	printf(" -------------------------\n");
}

bool compareBoards(char *winningBoard[4][4], char *playerBoard[4][4])
{
	int correctPosCount = 0;
	for (int i = 0; i<ROWS; i++)
	{
		for (int j = 0; j<COLUMNS; j++)
		{
			if ((strcmp(winningBoard[i][j], playerBoard[i][j])) != 0)
			{
				//printf("playerBoard != winningboard \n");
				return false;
			}
		}
	}
	return true;
}

struct matrixCoordinates locateMatrixCoords(char *str, char *playerBoard[4][4])
{
	struct matrixCoordinates matrixCoords;

	for (int i = 0; i<ROWS; i++)
	{
		for (int j = 0; j<COLUMNS; j++)
		{
			if ((strcmp(playerBoard[i][j], str)) == 0)
			{
				//printf("you entered: %s, i found it on playerBoard at: (%d, %d)\n", str, i, j);
				matrixCoords.x1 = i;
				matrixCoords.y1 = j;
			}
			if ((strcmp(playerBoard[i][j], "  ")) == 0)
			{
				//printf("i found the empty space on playerBoard at: (%d, %d)\n", i, j);
				matrixCoords.x2 = i;
				matrixCoords.y2 = j;
			}
		}
	}
	return matrixCoords;
}

bool tileIsAdjacent(struct matrixCoordinates matrixCoords)
{
	//input (x1, y1), empty (x2, y2)
	//printf("input @ (%d, %d), blank @ (%d, %d) \n", matrixCoords.x1, matrixCoords.y1, matrixCoords.x2, matrixCoords.y2);
	//printf("x2-1 = %d\n", matrixCoords.x2 - 1);
	//printf("x2+1 = %d\n", matrixCoords.x2 + 1);
	//printf("y2-1 = %d\n", matrixCoords.y2 - 1);
	//printf("y2+1 = %d\n", matrixCoords.y2 + 1);

	if (((matrixCoords.x1 == (matrixCoords.x2 - 1) || matrixCoords.x1 == (matrixCoords.x2 + 1)) && matrixCoords.y1 == matrixCoords.y2) ||
		((matrixCoords.y1 == (matrixCoords.y2 - 1) || matrixCoords.y1 == (matrixCoords.y2 + 1)) && matrixCoords.x1 == matrixCoords.x2))
	{
		//printf("tile was adjacent");
		return true;
	}
	
	return false;
}

void playTheGame(char *winningBoard[4][4], char *playerBoard[4][4])
{
	printf("Welcome to a simple text based tile game! The goal of the game is to get all the numbers into sequential order \n" \
		"left to right, top to bottom with the empty space at the end. Here is what a winning game board looks like: \n");
	boardPrinter(winningBoard);
	printf("To play the game, choose a number tile adjacant to the empty tile to swap them by typing exactly what is on the tile. \n" \
		"i.e: to swap tile \"03\" with the empty tile, type 03 \n\n");
	printf("This is what your board currently looks like! \n");
	boardPrinter(playerBoard);
	printf("Let's Begin!!!\n");

	struct matrixCoordinates matrixCoords;
	char *usrInptTile= malloc(64);

	while (!compareBoards(winningBoard, playerBoard))
	{
		printf("Please select a tile to swap with the empty tile: ");
		scanf("%s", usrInptTile);
		//if input is not a num or is not next to the empty
		while (!isdigit(*usrInptTile))
		{
			printf("you entered: %s which is not a number! Try again:", usrInptTile);
			scanf("%s", usrInptTile);
		}
		matrixCoords = locateMatrixCoords(usrInptTile, playerBoard); //input (x1, y1), empty (x2, y2)
		if (tileIsAdjacent(matrixCoords) )
		{
			swiperNoSwiping(playerBoard, matrixCoords);
		}
		else 
		{
			printf("\n*** %s is not adjacent to the empty tile. please try again! ***\n", usrInptTile);
		}
		
		boardPrinter(playerBoard);
	}

	//all tiles in correct place, compare boards was true
	printf("Congratulations!!! You won the game!\n");
}

int main()
{
	char *winningBoard[ROWS][COLUMNS] = {
		{"01", "02", "03", "04"},
		{"05", "06", "07", "08"},
		{"09", "10", "11", "12"},
		{"13", "14", "15", "  "}
	};

	char *playerBoard[ROWS][COLUMNS] = {
		{ "01", "02", "03", "04" },
		{ "05", "06", "07", "08" },
		{ "09", "10", "11", "12" },
		{ "13", "14", "15", "  " }
	};
	/*
	char *testBoard[ROWS][COLUMNS] = {
		{ "01", "02", "03", "04" },
		{ "05", "06", "07", "08" },
		{ "09", "10", "11", "12" },
		{ "13", "14", "  ", "15" }
	};
	*/
	boardRandomizer(playerBoard);
	playTheGame(winningBoard, playerBoard);

	system("pause");
	return 0;
}

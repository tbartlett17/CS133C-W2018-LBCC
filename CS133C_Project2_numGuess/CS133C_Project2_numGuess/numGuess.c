//********************************************************************************************
// Author: Tyler Bartlett
// File: numGuess.c
// Date: 02/05/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 2
// Desc: 1.	Ask a user to pick a data type, either int, long, or float.
//		 2.	Generate a secret number of that datatype and store that number into a variable.
//		 3.	Use a loop to repeatedly ask the user to guess by doing the following(you may choose how many guesses the user gets) :
//			a. Ask the user to guess the secret number.
//			b. Indicate what the range of possible numbers is so the user can make an informed guess.
//			c. Tell the user how many guesses they have left.
//			d. Tell the user whether they are too high, too low, or correct.
//		
//********************************************************************************************
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SECRET_INT 5
#define SECRET_LONG 3
#define SECRET_FLOAT 8.0
#define UPPER_BOUND 10.0
#define LOWER_BOUND 1.0
#define MAX_GUESS_COUNT 4

#define PRINT_HIGH 1
#define PRINT_LOW 2
#define PRINT_WIN 3
#define PRINT_LOSE 4

int printStatus(int guessCount, int printCase)
{

	switch (printCase)
	{
	case 1: //guess was too high
		guessCount--;
		if (guessCount == 0)
		{
			printStatus(guessCount, PRINT_LOSE);
			break;
		}
		printf("\n*** Your guess was too high! Please try again! (You have %d guesses remaing) ***\n", guessCount);
		break;
	case 2: //guess was too low
		guessCount--;
		if (guessCount == 0)
		{
			printStatus(guessCount, PRINT_LOSE);
			break;
		}
		printf("\n*** Your guess was too low! Please try again! (You have %d guesses remaing) ***\n", guessCount);
		break;
	case 3: //guess was correc
		guessCount = 0;
		printf("\n*** Good job! you guessed the secret number! :) Thanks for playing! ***\n");
		break;

	case 4: //you loose
		printf("\n*** You failed to guess the secret number :( Better luck next time! ***\n");
		break;
	default:
		printf("How did you get here???\n");
		break;
	}

	return guessCount;
}

void guessTheNumber(float secretNumber, float lowerBound, float upperBound, int guessCount)
{
	float *usrGuess = malloc(64);
	int tickingTimeBomb = 0;
	float sscanfResult;
	float guess = 0;

	printf("You have %d tries to guess the secret number.\n", guessCount);
	while (guessCount !=0)
	{
		printf("Please enter your guess as to what the secret number is between %.1f and %.1f (inclusive): ", lowerBound, upperBound);
		scanf( "%f", usrGuess);

		/* 
		TRIED TO GET DATA VALIDATION TO WORK FOR NON_NUMERICAL CHARS. WORKED WHEN
		I DID THIS FOR ARRAYS BUT DOES NOT SEEM TO WORK WITH POINTERS?
		*/

		//sscanfResult = sscanf(usrGuess, "%f", &guess);
		//printf("sscanfResult is: %d", sscanfResult);

		if ((*usrGuess < lowerBound) || (*usrGuess > upperBound) /*|| (sscanfResult == 0) | (sscanfResult == EOF) */)
		{
			printf("\n*** Your guess was out of bounds or you did not enter a number! Please try again! ***\n");
			tickingTimeBomb++;
			if (tickingTimeBomb == 75)
			{
				printf("\n*** You entered a non-numerical answer and got the program stuck in a loop. ***\n");
				printf("*** I am here to save you, user! (By quitting the program) ***\n");
				system("pause");
				exit(0);
			}
		}
		else if (*usrGuess < secretNumber)
		{
			guessCount = printStatus(guessCount, PRINT_LOW);
		}
		else if (*usrGuess > secretNumber)
		{
			guessCount = printStatus(guessCount, PRINT_HIGH);
		}
		else
		{
			guessCount = printStatus(guessCount, PRINT_WIN);
		}

	}
	free(usrGuess);
}

int main()
{
	/* pointers for user input string and comparing input to datatype */
	char *usrInptDataType = malloc(64);
	char *typeInt = "int";
	char *typeLong = "long";
	char *typeFloat = "float";

	printf("Please choose a data type from the following list: \"%s\", \"%s\", or \"%s\" \n", typeInt, typeLong, typeFloat);
	
	bool invalidDataType = true;
	while (invalidDataType)
	{
		scanf("%s", usrInptDataType);

		/* Compare usrInpt pointer to dataType pointers */
		if ((strcmp(usrInptDataType, typeInt)) == 0)
		{
			invalidDataType = false;
			printf("you chose int!\n");
			guessTheNumber((float)SECRET_INT, LOWER_BOUND, UPPER_BOUND, MAX_GUESS_COUNT);
		}
		else if ((strcmp(usrInptDataType, typeLong)) == 0)
		{
			printf("you chose long!\n");
			invalidDataType = false;
			guessTheNumber((float)SECRET_LONG, LOWER_BOUND, UPPER_BOUND, MAX_GUESS_COUNT);
		}
		else if ((strcmp(usrInptDataType, typeFloat)) == 0)
		{
			printf("you chose float!\n");
			invalidDataType = false;
			guessTheNumber(SECRET_FLOAT, LOWER_BOUND, UPPER_BOUND, MAX_GUESS_COUNT);
		}
		else
		{
			printf("Your input of \"%s\" did not match \"%s\", \"%s\", or \"%s\"," \
				"Please pick a valid data type. \n", usrInptDataType, typeInt, typeLong, typeFloat);
		}
	}
	free(usrInptDataType);

	system("pause");
	return 0;
}
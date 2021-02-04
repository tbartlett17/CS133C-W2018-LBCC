//********************************************************************************************
// Author: Tyler Bartlett
// File: strings.c
// Date: 01/29/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Lab: 4
// Desc: This program retrieves wight, height, and age from user and computes clothing sizes 
//			according to the following formulas:
//			1. Hat size = weight in pounds divided by height in inches then multiplied by 2.9
//			2. Jacket size(chest in inches) = height times weight divided by 288 and then 
//				adjusted by adding one - eighth of an inch for each 10 years over age 30
//			3. Waist in inches = weight divided by 5.7 and then adjusted by adding one - tenth
//				of an inch for each 2 years over age 28
//			print the user weight, height, and age and their calculated clothing sizes.
//			this whole process should be repeatable.
//********************************************************************************************
#include <stdio.h>
#include <stdbool.h>

#define AGE_REQUEST 1
#define HEIGHT_REQUEST 2
#define WEIGHT_REQUEST 3
#define QUIT_REQUEST 4

#define MIN_AGE 1
#define MAX_AGE 123 /* years - world record for longest life */
#define MIN_HEIGHT 29 /* inches - average height for 1 year olds */
#define MAX_HEIGHT 108 /* inches (9 ft) - world record for tallest person */
#define MIN_WEIGHT 19 /* lbs - avaerage weight for 1 year old */
#define MAX_WEIGHT 1400 /* lbs - world record for heaviest person */

void printWelcome()
{
	printf("Welcome to sizes.c! this program will ask you to enter your age, height, and "
		"weight and will then calculate and display \n"); 
	printf("your clothing sizes (hat size, jacket size, and waist size). \n\n");
}

int inputRequestAndValidate(int inputCase)
{
	char line[100]; /* A line to be read from terminal*/
	int userInput;
	int sscanfResult;
	bool invalid = true;
	
	switch (inputCase)
	{
		case 1: /* AGE_INPUT */
			while (invalid)
			{
				printf("Please enter your age in years rounded up to the next highest integer: ");
				fgets(line, sizeof(line), stdin);
				sscanfResult = sscanf_s(line, "%d", &userInput); /* pull an int from userInput */
				//printf("sscanf is: %d, userinput is: %d\n", sscanfResult, userInput);

				/* check for value out of bounds, a non-int value, or end of file */
				if ((userInput < MIN_AGE) || (userInput > MAX_AGE) || (sscanfResult == 0) | (sscanfResult == EOF))
				{
					printf("\n*** You have to enter a positive integer! Try Again! ***\n");
				}
				else
				{
					invalid = false;
				}
			}
			break;
		case 2: /* HEIGHT_INPUT */
			while (invalid)
			{
				printf("Please enter your height in inches rounded to the nearest whole intenger: ");
				fgets(line, sizeof(line), stdin);
				sscanfResult = sscanf_s(line, "%d", &userInput); /* pull an int from userInput */
				//printf("sscanf is: %d, userinput is: %d\n", sscanfResult, userInput);

				/* check for value out of bounds, a non-int value, or end of file */
				if ((userInput < MIN_HEIGHT) || (userInput > MAX_HEIGHT) || (sscanfResult == 0) | (sscanfResult == EOF))
				{
					printf("\n*** You have to enter a positive integer! Try Again! ***\n");
				}
				else
				{
					invalid = false;
				}
			}
			break;
		case 3: /* WEIGHT_INPUT */
			while (invalid)
			{
				printf("Please enter your weight in lbs rounded to the nearest whole integer: ");
				fgets(line, sizeof(line), stdin);
				sscanfResult = sscanf_s(line, "%d", &userInput); /* pull an int from userInput */
				//printf("sscanf is: %d, userinput is: %d\n", sscanfResult, userInput);

				/* check for value out of bounds, a non-int value, or end of file */
				if ((userInput < MIN_WEIGHT) || (userInput > MAX_WEIGHT) || (sscanfResult == 0) | (sscanfResult == EOF))
				{
					printf("\n*** You have to enter a positive integer! Try Again! ***\n");
				}
				else
				{
					invalid = false;
				}
			}
			break;
		case 4:/* QUIT_REQUEST */
			while (invalid)
			{
				printf("\nWould you like to run another set of calculations? (1 for yes, 0 for no): ");
				fgets(line, sizeof(line), stdin);
				sscanfResult = sscanf_s(line, "%d", &userInput); /* pull an int from userInput */
				//printf("sscanf is: %d, userinput is: %d\n", sscanfResult, userInput);

				/* check for value out of bounds, a non-int value, or end of file */
				if ((sscanfResult == 0) | (sscanfResult == EOF))
				{
					printf("\n*** You have to enter a positive integer! Try Again! ***\n");
				}
				else if (userInput == 1)
				{
					invalid = false;
				}
				else if (userInput == 0)
				{
					userInput = 9999;
					invalid = false;
				}
				else
				{
					printf("\n*** You have to enter a positive integer! Try Again! ***\n");
				}
			}
			break;
		default:
			printf("I am not sure what you did to get here but there is a serious error. \n");
			break;
	}
	return userInput;
}

double hatSizeCalc(int height, int weight)
{
	double hatSize = ( ((double) weight) / ((double) height)) * (2.9);
	//printf("your hat size is: %f\n", hatSize);
	return hatSize;
}

double jacketSizeCalc(int age, int height, int weight)
{
	double jacketSize =  (((double) height) * ( (double) weight)) / (288);

	if (age >= 40)
	{
		double ageMod = 0.13; /* 1/8th of an inch */
		int ageModMultiplier = 0;
		int i = 40;
		while ( i < age)
		{
			i += 10;
			ageModMultiplier += 1;
		}
		//printf("ageModMultiplier is: %d\n", ageModMultiplier);
		jacketSize = jacketSize + ((ageMod)*(ageModMultiplier));
	}
	//printf("jacket size is: %f\n", jacketSize);
	return jacketSize;
}

double waistSizeCalc(int age, int height, int weight)
{
	//Waist in inches = weight divided by 5.7 and then adjusted by adding one - tenth
	//of an inch for each 2 years over age 28
	double waistSize = ((double) weight) / (5.7);

	if (age >= 30)
	{
		double ageMod = 0.1;
		int ageModMultiplier = 0;
		int i = 30;
		while (i < age)
		{
			i += 2;
			ageModMultiplier += 1;
		}
		//printf("ageModMultiplier is: %d\n", ageModMultiplier);
		waistSize = waistSize + ((ageMod)*(ageModMultiplier));
	}
	//printf("waistSize is: %f\n", waistSize);
	return waistSize;
}

void statPrinter(int age, int height, int weight, double hatSize, double jacketSize, double waistSize)
{
	printf("\nThe clothing sizes for a %d year old person, %d inches tall, and weighing %d lbs are: \n"
		"Hat Size: %f\nJacket (chest) Size: %f inches\nWaist Size: %f inches\n", 
		age, height, weight, hatSize, jacketSize, waistSize);
}

int main()
{
	int age, height, weight;
	double hatSize, jacketSize, waistSize;
	bool continueCalcs = true;
	
	printWelcome();

	while (continueCalcs)
	{
		/* Get input */
		age = inputRequestAndValidate(AGE_REQUEST);
		height = inputRequestAndValidate(HEIGHT_REQUEST);
		weight = inputRequestAndValidate(WEIGHT_REQUEST);

		/* Perform clothing size calculations */
		hatSize = hatSizeCalc(height, weight);
		jacketSize = jacketSizeCalc(age, height, weight);
		waistSize = waistSizeCalc(age, height, weight);

		/* Print the goodies */
		statPrinter(age, height, weight, hatSize, jacketSize, waistSize);

		/* More calculations? */
		if (inputRequestAndValidate(QUIT_REQUEST) == 9999)
		{
			continueCalcs = false;
		}
	}
	return 0;
}
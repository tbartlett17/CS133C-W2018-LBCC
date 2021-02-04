//********************************************************************************************
// Author: Tyler Bartlett
// File: strings.c
// Date: 01/26/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Lab: 3
// Desc: This program retrieves a string from the user, saves it to a char array
//			and prints it. The array is flipped and reprinted afterwards.
//********************************************************************************************
#include <stdio.h>
#include <string.h> //used for strlen which returns the size of the string

#define MAX 200

void printWelcome()
{
	printf("Welcome to strings.c! This program will get input from the user and print it one "
		"character at a time fowards, then print it one character at a time backwards. \n");
}

int getInpt(char usrInpt[])
{
	printf("please enter a string (max of 200 characters): ");
	fgets(usrInpt, MAX, stdin);

	return usrInpt;
}

/* Override newline character with NULL and fill rest of array with NULL */
int fixInpt(char usrInpt[])
{
	for (int i = (strlen(usrInpt)-1); i < MAX; i++)
	{
		usrInpt[i] = '\0';
	}
	return usrInpt;
}

void printFowardAndBackwards(char usrInpt[])
{
	printf("Printing one character at a time fowards: \n");
	for (int i = 0; usrInpt[i] != '\0'; i++)
	{
		printf("%c\n", usrInpt[i]);
	}

	printf("Printing one character at a time backwards: \n");
	for (int i = (MAX - 1); i >= 0; i--)
	{
		if (usrInpt[i] != '\0')
		{
			printf("%c\n", usrInpt[i]);
		}
	}
}

int main()
{
	/*
	from what i saw online, i feel like using malloc, realloc, and pointers to create a dynamically
	sized array to the length of the user input is the correct way to do this? that way i can
	prevent issues of users walking out of the size of my array.

	char *usrInpt = malloc(TEMP_BUFFER * sizeof *usrInpt); //create a pointer and allocate memmory for it
	char *tmp = realloc(usrInpt, TEMP_BUFFER * sizeof *usrInpt);
	*/

	char usrInpt[MAX];
	printWelcome();
	getInpt(usrInpt);
	fixInpt(usrInpt);
	printFowardAndBackwards(usrInpt);

	system("pause"); //added to make the program not automatically close after completion 
	return 0;
}

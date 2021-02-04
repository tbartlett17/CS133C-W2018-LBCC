//********************************************************************************************
// Author: Tyler Bartlett
// File: vowels.c
// Date: 02/05/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Lab: 5
// Desc: 1.	Request a phrase from the user.
//		 2.	Display all the vowels in the phrase.
//		 3.	Display all characters that are NOT vowels in the phrase.
//		 4.	Use ONLY pointers not arrays in this program.
//		
//********************************************************************************************
#include <stdio.h>
#include <string.h>

#define MAX 200

void getInput(char *pointer)
{
	printf("please enter a string (max of 200 characters): ");
	fgets(pointer, MAX, stdin);
	if ((pointer = strchr(pointer, '\n')) != NULL)
	{
		*pointer = '\0';
	}
}

void vowelPrinter(char *pos)
{
	printf("Printing just the vowels from what you entered (seperated by commas): \n");
	for (int i = 0; *pos != '\0'; i++)
	{
		if (*pos == 'a' || *pos == 'e' || *pos == 'i' || *pos == 'o' || *pos == 'u' ||
			*pos == 'A' || *pos == 'E' || *pos == 'I' || *pos == 'O' || *pos == 'U')
		{
			printf("%c, ", *pos);
		}
		pos++;
	}
	printf("\n\n");
}

void nonVowelPrinter(char *pos)
{
	printf("Printing the non-vowel characters from what you entered (seperated by commas): \n");
	for (int i = 0; *pos != '\0'; i++)
	{
		if (*pos == 'a' || *pos == 'e' || *pos == 'i' || *pos == 'o' || *pos == 'u' ||
			*pos == 'A' || *pos == 'E' || *pos == 'I' || *pos == 'O' || *pos == 'U')
		{
			//do nothing
		}
		else
		{
			printf("%c, ", *pos);
		}
		pos++;
	}
	printf("\n\n");
}

int main()
{
	char userInput[MAX];
	char *pointerToInputArr;
	pointerToInputArr = userInput;

	getInput(pointerToInputArr);
	
	vowelPrinter(pointerToInputArr);
	nonVowelPrinter(pointerToInputArr);
	
	system("pause"); //added to make the program not automatically close after completion 
	return 0;
}
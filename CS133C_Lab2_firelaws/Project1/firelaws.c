//********************************************************************************************
// Author: Tyler Bartlett
// File: firelaws.c
// Date: 01/22/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Lab: 2
// Desc: This program reports the legality of holding a meeting
//			in a room based on local fire laws
//********************************************************************************************
#include <stdio.h>

int main()
{
	int maxRoomCap, attendeeCount;
	printf("Welcome to firelaws! This program reports the legality of holding a meeting "
		"in a room based on local fire laws. \n");
	maxRoomCap = inputRequest(1); //get max room count
	attendeeCount = inputRequest(2); //get amount of people atteding the meeting
	compare(maxRoomCap, attendeeCount);
	
	system("pause"); //added to make the program not automatically close after completion 
	return 0;
}

int inputRequest(int inputCase)
{
	int userInput;
	//input request for max room cap
	if (inputCase == 1)
	{
		printf("Please enter the maximum capacity of people for your meeting room as a number: ");
		scanf_s("%d", &userInput);
	}
	//input request for attendee count
	if (inputCase == 2)
	{
		printf("Please enter the number of people attending the meeting as a number: ");
		scanf_s("%d", &userInput);
	}
	return userInput;
}

/* Determines legality of meeting */
int compare(int roomCap, int numPeople)
{
	int diff;
	if (roomCap > numPeople)
	{
		diff = roomCap - numPeople;
		printf("It is legal to hold your meeting in this room. An additional %d people may attend "
			"if desired. \n", diff);
	}
	else if (roomCap == numPeople)
	{
		printf("It is legal to hold your meeting in this room but no additional people may attend. \n");
	}
	else
	{
		diff = numPeople - roomCap;
		printf("It is illegal to hold your meeting in this room because you have exceeded the "
			"maximum capacity of the room. %d people must be excluded to conform with local firelaws. \n", diff);
	}
	return 0;
}
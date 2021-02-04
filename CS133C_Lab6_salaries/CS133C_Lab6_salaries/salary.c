//********************************************************************************************
// Author: Tyler Bartlett
// Files: salary.c, Employee_Salary_Info.txt, 
// Date: 02/09/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Lab: 6
// Desc: Read in employee salary data from a txt file and write to two files based off
// 	 employee rank
//		
//********************************************************************************************
#include <stdio.h>

int processE(FILE *fileE, double yearlySalary, double bonus, double extraBonus, int employeeID, char employeeType[])
{
	fprintf(fileE, "%d\t%s\t%.2f\t%.2f \t%.2f\t%.2f\n", employeeID, employeeType,
		yearlySalary, bonus, extraBonus, (yearlySalary+bonus+extraBonus));
	return 0;
}

int processNP(FILE *fileNP, double yearlySalary, double bonus, int employeeID, char employeeType[])
{
	fprintf(fileNP, "%d\t%s\t%.2f \t%.2f\t%.2f\n", employeeID, employeeType,
		yearlySalary, bonus, (yearlySalary + bonus));
	return 0;
}

int main()
{
	/* File Pointers */
	FILE *fpIN;
	FILE *fpOutNP;
	FILE *fpOutE;

	/* File Names for IO */
	char *inputFile = "Employee_Salary_Info.txt";
	char *outputFileE = "Employee_Salary_E.txt";
	char *outputFileNP = "Employee_Salary_NP.txt";

	/* Variable Types from inputFile */
	int employeeID;
	char employeeType[2];
	float hourlyRate, totalHours, bonusRate;
	
	/* A buffer for fgets */
	char line[100];

	/* Open File to Read */
	fpIN = fopen(inputFile, "r");

	if (fpIN == NULL)
	{
		printf("Error opening file: %s\n", inputFile);
		printf("Terminating program... please include \"%s\" in the same directory\n", inputFile);
		printf("of this program before running again.\n");
		system("pause"); //added to make the program not automatically close after completion 
		exit(); //shut down program to avoid crash
	}
	else
	{
		/* If File Opened for Read was Successful, Open Files to Write */
		fpOutE = fopen(outputFileE, "w");
		fpOutNP = fopen(outputFileNP, "w");

		fgets(line, 100, fpIN); // throw out line one of file
		printf("calculating employee salaries...\n");

		/* Read from input File, Write to Output Files */
		while ( (fscanf(fpIN, "%d %s %f %f %f", &employeeID, employeeType, &hourlyRate, &totalHours, &bonusRate)) !=EOF )
		{
			//printf("employee type from file is: %s\n", employeeType);
			if (employeeType[0] == 'E')
			{
				//printf("employee type was E \n");
				processE(fpOutE, (hourlyRate*totalHours), (hourlyRate*totalHours*bonusRate),
					(hourlyRate*totalHours*0.1), employeeID, employeeType);
			}
			else
			{
				//printf("employee type was N/P \n");
				processNP(fpOutNP, (hourlyRate*totalHours), (hourlyRate*totalHours*bonusRate),
					employeeID, employeeType);
			}
			
			//printf("%d\n%s\n%.2f\n%.2f\n%.2f\n\n", employeeID, employeeType, hourlyRate, totalHours, bonusRate);
		}
	}
	printf("done! check \"Employee_Salary_E.txt\" and \"Employee_Salary_NP.txt\"\n");
	
	fclose(fpIN);
	fclose(fpOutE);
	fclose(fpOutNP);

	system("pause"); //added to make the program not automatically close after completion 
	return 0;
}
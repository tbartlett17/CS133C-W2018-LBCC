//********************************************************************************************
// Author: Tyler Bartlett
// Files: matrixMadness.c, matrix1.txt, matrix2.txt, matrix3.txt
// Date: 03/12/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 5
// Desc: read in a matrix from a .txt file, add it to itself, multiply the result by the original, divide the result by the original
//		
//********************************************************************************************
#define _CRT_SECURE_NO_WARNINGS// shutup stupid compiler

#include <stdio.h> 
#include <stdlib.h>

/* File Names for IO */
#define MATRIX1 "matrix1.txt"
#define MATRIX2 "matrix2.txt"
#define MATRIX3 "matrix3.txt"

int rowCounter(FILE *filePtr)
{
	int rowCount = 1;
	int ch;

	while ((ch = fgetc(filePtr)) != EOF)
	{
		if (ch == '\n')
		{
			rowCount++;
		}
	}
	rewind(filePtr);
	//printf("row count:%d\n", rowCount);
	return rowCount;
}

int colCounter(FILE *filePtr)
{
	int colCount = 1;
	int ch;

	while ((ch = fgetc(filePtr)) != '\n')
	{
		//printf("ch was: %c\n", ch);
		if (ch == '\t')
		{
			colCount++;
		}
	}
	rewind(filePtr);
	//printf("col count:%d\n", colCount);
	return colCount;
}

int **matrixConstructor(int rowCount, int colCount)
{
	int **dynamicMatrix;
	dynamicMatrix = malloc(rowCount * sizeof(int*));
	for (int i = 0; i < rowCount; i++)
	{
		dynamicMatrix[i] = malloc(colCount * sizeof(int));
	}
	return dynamicMatrix;
}

void populateMatrixFromFile(FILE *filePtr, int **matrix, int rowCount, int colCount)
{	
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			fscanf(filePtr, "%d", &matrix[i][j]);
		}
	}
}

void copyMatrix(int **originalMatrix, int **copyMatrix, int rowCount, int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			copyMatrix[i][j] = originalMatrix[i][j];
		}
	}
}

void matrixPrinter(int **matrix, int rowCount, int colCount)
{
	for (int j = 0; j<colCount; j++)
	{
		for (int i = 0; i<rowCount; i++)
		{
				printf("%d\t", matrix[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void addToSelf(int **matrix, int rowCount, int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			matrix[i][j] += matrix[i][j];
		}
	}
}

void multiplier(int **tempMatrix, int **originalMatrix, int rowCount, int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			tempMatrix[i][j] = (tempMatrix[i][j])*(originalMatrix[i][j]);
		}
	}
}

void divider(int **tempMatrix, int **originalMatrix, int rowCount, int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			if (originalMatrix[i][j] != 0)
			{
				tempMatrix[i][j] = (tempMatrix[i][j]) / (originalMatrix[i][j]);
			}
		}
	}
}

void matrixManipulator(FILE *fp)
{
	int rowCount = rowCounter(fp);
	int colCount = colCounter(fp);
	int **dynamicMatrix = matrixConstructor(rowCount, colCount);
	int **tempMatrix = matrixConstructor(rowCount, colCount);

	populateMatrixFromFile(fp, dynamicMatrix, rowCount, colCount);
	copyMatrix(dynamicMatrix, tempMatrix, rowCount, colCount);

	printf("The original matrix:\n");
	matrixPrinter(dynamicMatrix, rowCount, colCount);

	printf("The original matrix added to itself: \n");
	addToSelf(tempMatrix, rowCount, colCount);
	matrixPrinter(tempMatrix, rowCount, colCount);

	printf("The original matrix multiplied by the previous matrix: \n");
	multiplier(tempMatrix, dynamicMatrix, rowCount, colCount);
	matrixPrinter(tempMatrix, rowCount, colCount);

	printf("The previous matrix divided by the original matrix: \n");
	divider(tempMatrix, dynamicMatrix, rowCount, colCount);
	matrixPrinter(tempMatrix, rowCount, colCount);
	printf("**************************************************************\n");
}

int main()
{
	/* File Pointers and Open Files to Read */
	FILE *fpMatrixIN1 = fopen(MATRIX1, "r");
	FILE *fpMatrixIN2 = fopen(MATRIX2, "r");
	FILE *fpMatrixIN3 = fopen(MATRIX3, "r");

	/* Check File Pointers for Null, Exit if Null */
	if (fpMatrixIN1 == NULL || fpMatrixIN2 == NULL || fpMatrixIN3 == NULL)
	{
		printf("One or more files failed to be found. Please make sure they are in the same directory as the executable.\n");
		system("pause"); //added to make the program not automatically close after completion 
		exit(1); //shut down program to avoid crash
	}
	
	/* Do the Stuff and Things */
	matrixManipulator(fpMatrixIN1);
	matrixManipulator(fpMatrixIN2);
	matrixManipulator(fpMatrixIN3);

	fclose(fpMatrixIN1);
	fclose(fpMatrixIN2);
	fclose(fpMatrixIN3);

	return 0;
}
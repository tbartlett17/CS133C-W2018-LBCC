//********************************************************************************************
// Author: Tyler Bartlett
// Files: supplies.c, products.txt, suppliers.txt
// Date: 02/26/18
// Course: CS 133C
// Class time: 8am, M/W/F
// Project: 4
// Desc: I think this reads supplier and product info tables from txt files then prints 
// 	 whatever information I decided was relevant.
// 	 asks user for what shit to order and writes an order receipt.
//		
//********************************************************************************************
#define _CRT_SECURE_NO_WARNINGS// shutup stupid compiler

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define NUM_SUPPLIERS 5
#define NUM_PRODUCTS 10
#define BUFFER 100
#define SUPPLIERS_FILE "suppliers.txt"
#define PRODUCTS_FILE "products.txt"
#define RECIEPT_FILE "receipt.txt"

struct supplierInfo {
	int supplierID;
	char supplierName[BUFFER];
	char supplierState[BUFFER];
	char supplierPhoneNum[BUFFER];
	char supplierWebsite[BUFFER];
} ;

struct productInfo {
	int productID;
	char productName[BUFFER];
	int supplierID;
	float price;
	int inventory;
};

struct invoice {
	int orderQuantity;
	char* productName;
	char* supplierName;
	float pricePerUnit;
};

void populateSuppliersArr(FILE *filePtr, struct supplierInfo (*ptrToSuppliersArr)[])
{
	struct supplierInfo* supplierPtr = malloc(NUM_SUPPLIERS * sizeof(struct supplierInfo));
	char line[BUFFER];
	fgets(line, BUFFER, filePtr); // throw out line one of suppliers file

	for (int i = 0; fscanf(filePtr, "%d %s %s %s %s", &supplierPtr->supplierID, supplierPtr->supplierName,
		supplierPtr->supplierState, supplierPtr->supplierPhoneNum, supplierPtr->supplierWebsite) != EOF; i++)
	{
		(*ptrToSuppliersArr)[i].supplierID = supplierPtr->supplierID;
		strcpy((*ptrToSuppliersArr)[i].supplierName, supplierPtr->supplierName);
		strcpy((*ptrToSuppliersArr)[i].supplierState, supplierPtr->supplierState);
		strcpy((*ptrToSuppliersArr)[i].supplierPhoneNum, supplierPtr->supplierPhoneNum);
		strcpy((*ptrToSuppliersArr)[i].supplierWebsite, supplierPtr->supplierWebsite);
	}
}

void populateProductsArr(FILE *filePtr, struct productInfo(*ptrToProductsArr)[])
{
	struct productInfo* productPtr = malloc(NUM_PRODUCTS * sizeof(struct productInfo));
	char line[BUFFER];
	fgets(line, BUFFER, filePtr); // throw out line one of products file

	for (int i = 0;  fscanf(filePtr, "%d %s %d %f %d", &productPtr->productID, productPtr->productName,
		&productPtr->supplierID, &productPtr->price, &productPtr->inventory) != EOF; i++)
	{
		(*ptrToProductsArr)[i].productID = productPtr->productID;
		strcpy((*ptrToProductsArr)[i].productName, productPtr->productName);
		(*ptrToProductsArr)[i].supplierID = productPtr->supplierID;
		(*ptrToProductsArr)[i].price = productPtr->price;
		(*ptrToProductsArr)[i].inventory = productPtr->inventory;
	}
}

void printSupplierProducts(struct supplierInfo(*ptrToSuppliersArr)[], struct productInfo(*ptrToProductsArr)[])
{
	for (int i = 0; i < NUM_SUPPLIERS; i++)
	{
		printf("Products available from %s:\n", (*ptrToSuppliersArr)[i].supplierName);

		for (int j = 0; j < NUM_PRODUCTS; j++)
		{
			if ((*ptrToProductsArr)[j].supplierID == (*ptrToSuppliersArr)[i].supplierID)
			{
				printf("\t\t%s @ $%.2f ea\n", (*ptrToProductsArr)[j].productName, (*ptrToProductsArr)[j].price);
			}
		}
		printf("\n");
	}
}

char* findSupplierName(struct supplierInfo(*ptrToSuppliersArr)[], int supplierID)
{
	char* supplierName;
	for (int i = 0; i < NUM_SUPPLIERS; i++)
	{
		if (supplierID == (*ptrToSuppliersArr)[i].supplierID)
		{
			supplierName = (*ptrToSuppliersArr)[i].supplierName;
			//printf("found %s\n", supplierName);
		}
	}
	return supplierName;
}

void writeReciept(FILE *filePtr, struct invoice invoice)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char dateAndTime[64];
	strftime(dateAndTime, sizeof(dateAndTime), "%c", tm);
	//printf("%s\n", dateAndTime);

	fprintf(filePtr, "You ordered: %d units of %s from %s @ %.2f ea on %s\n", invoice.orderQuantity,
		invoice.productName, invoice.supplierName, invoice.pricePerUnit, dateAndTime);
}

void orderProducts(FILE *filePtr, struct supplierInfo(*ptrToSuppliersArr)[], struct productInfo(*ptrToProductsArr)[])
{
	int quantity;
	float totalPrice = 0;
	//char line[BUFFER];
	bool continueOrder = true;
	char *userInput = malloc(64);
	char* quitter = "done";
	struct invoice invoice;

	printf("Type \"done\" at any time to complete your order and checkout.\n");
	
	while (continueOrder)
	{
		printf("Enter the name of the product you wish to order (exactly as it is typed): ");
		scanf("%s", userInput);

		if (strcmp(userInput, quitter) == 0)
		{
			continueOrder = false;
			printf("Please enter your name to finalize your order:");
			scanf("%s", userInput);
			fprintf(filePtr, "\n\n order finalized by %s. \n Your Total for this order is: %.2f", userInput, totalPrice);
		}

		for (int i = 0; i < NUM_PRODUCTS; i++)
		{
			if (strcmp(userInput, (*ptrToProductsArr)[i].productName) == 0)
			{
				printf("Enter a quantity to order: ");
				scanf("%s", userInput);
				while (!isdigit(*userInput))
				{
					printf("you entered: %s which is not a number! Try again:", userInput);
					scanf("%s", userInput);
				}
				quantity = atoi(userInput);
				if (quantity > (*ptrToProductsArr)[i].inventory)
				{
					printf("error, supplier only has %d available units of %s. Cant fulil this order, try again.\n",
						(*ptrToProductsArr)[i].inventory, (*ptrToProductsArr)[i].productName);
				}
				invoice.productName = (*ptrToProductsArr)[i].productName;
				invoice.supplierName = findSupplierName(ptrToSuppliersArr, (*ptrToProductsArr)[i].supplierID);
				invoice.orderQuantity = quantity;
				invoice.pricePerUnit = (*ptrToProductsArr)[i].price;
				writeReciept(filePtr, invoice);
				totalPrice += (*ptrToProductsArr)[i].price * quantity;
			}
		}
	}
}

int main()
{
	/* File Names for IO */
	char *inputFileSuppliers = "suppliers.txt";
	char *inputFileProducts = "products.txt";
	char *outputFileCustomerReceipt = "reciept.txt";

	/* File Pointers and Open Files to Read */
	FILE *fpSuppliersIN = fopen(SUPPLIERS_FILE, "r");
	FILE *fpProductsIN = fopen(PRODUCTS_FILE, "r");

	/* Check File Pointers for Null, Exit if Null */
	if (fpProductsIN == NULL)
	{
		printf("Error opening file: %s\n", inputFileProducts);
		printf("Terminating program... please include \"%s\" in the same directory\n", inputFileProducts);
		printf("of this program before running again.\n");
		system("pause"); //added to make the program not automatically close after completion 
		exit(1); //shut down program to avoid crash
	}
	if (fpSuppliersIN == NULL)
	{
		printf("Error opening file: %s\n", inputFileSuppliers);
		printf("Terminating program... please include \"%s\" in the same directory\n", inputFileSuppliers);
		printf("of this program before running again.\n");
		system("pause"); //added to make the program not automatically close after completion 
		exit(1); //shut down program to avoid crash
	}

	/* Open Output File for Write */
	FILE *fpRecieptOUT = fopen(RECIEPT_FILE, "w");

	/* Suppliers and Products Arrays and their Pointers */
	struct supplierInfo suppliersArr[NUM_SUPPLIERS];
	struct productInfo productsArr[NUM_PRODUCTS];
	struct supplierInfo (*ptrToSuppliersArr)[] = &suppliersArr;
	struct productInfo(*ptrToProductsArr)[] = &productsArr;

	populateSuppliersArr(fpSuppliersIN, ptrToSuppliersArr);
	populateProductsArr(fpProductsIN, ptrToProductsArr);

	printSupplierProducts(ptrToSuppliersArr, ptrToProductsArr);
	orderProducts(fpRecieptOUT, ptrToSuppliersArr, ptrToProductsArr);


	/* Print Suppliers and Products Arrays */
/*
	for (int i = 0; i < NUM_SUPPLIERS; i++)
	{
		printf("supplierID: %d\n", suppliersArr[i].supplierID);
		printf("supplierName: %s\n", suppliersArr[i].supplierName);
		printf("supplierState: %s\n", suppliersArr[i].supplierState);
		printf("supplierPhoneNum: %s\n", suppliersArr[i].supplierPhoneNum);
		printf("supplierWebsite: %s\n\n", suppliersArr[i].supplierWebsite);
	}

	for (int i = 0; i < NUM_PRODUCTS; i++)
	{
		printf("ProductID: %d\n", productsArr[i].productID);
		printf("ProductName: %s\n", productsArr[i].productName);
		printf("SupplierID: %d\n", productsArr[i].supplierID);
		printf("ProductPrice: %.2f\n", productsArr[i].price);
		printf("ProductInventory: %d\n\n", productsArr[i].inventory);
	}
*/
	

	fclose(fpSuppliersIN);
	fclose(fpProductsIN);
	fclose(fpRecieptOUT);

	return 0;
}
/*
Name:		 Adam Springett
ID:			 130751209
Email:		 aspringett@myseneca.ca
Section:	 NOO
Date:		 Dec 6, 2020
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "stock.h"

void clearBuffer(void)
{
	while (getchar() != '\n')
		//Do nothing
		;
}


int readStockItems(struct StockRecord stockRecord[], int max, int input)
{
	int i = 0, keepGoing = 1, counter = 0, analyzing = 1, byWeight;
	
	if (input == 1)
	{
		for (i = 0; i < max && analyzing; i++)
		{
			counter++;
			stockRecord[i].id = counter;
			scanf("%lf,%d,%lf,%d,%30[^\n]", &stockRecord[i].
				quantity, &stockRecord[i].stockInfo.category, &stockRecord[i].stockInfo.price, &byWeight, &stockRecord[i].itemName);
			clearBuffer();

			if (stockRecord[i].quantity == 0)
			{
				analyzing = 0;
				keepGoing = 0;
				stockRecord[i].stockInfo.category = 1;
			}

			do
			{
				if (stockRecord[i].stockInfo.category < 1 || stockRecord[i].stockInfo.category > 7)
				{
					printf("Invalid Category - Enter a number between 1 and 7: ");
					scanf("%d,%lf,%d,%30[^\n]", &stockRecord[i].stockInfo.category, &stockRecord[i].stockInfo.price, &stockRecord[i].stockInfo.byWeight, &stockRecord[i].itemName);
					clearBuffer();
				}
				else
				{
					keepGoing = 0;
				}
			} while (keepGoing);


			do
			{
				if (stockRecord[i].stockInfo.byWeight == 1 || stockRecord[i].stockInfo.byWeight == 0)
				{
					keepGoing = 0;
				}
				else
				{
					printf("Invalid soldByWeight - Enter a number between 0 and 1: ");
					scanf("%d,%30[^\n]", &stockRecord[i].stockInfo.byWeight, &stockRecord[i].itemName);
					clearBuffer();
					keepGoing = 1;
				}
			} while (keepGoing);
		}
	}

	return counter;
}

void productType(struct StockRecord stockRecord[])
{
	int i = 0;

	switch (stockRecord[i].stockInfo.category)
	{
	case 1:
		printf("%16s", "produce");
		break;
	case 2:
		printf("%16s", "bakery");
		break;
	case 3:
		printf("%16s", "meat");
		break;
	case 4:
		printf("%16s", "dairy");
		break;
	case 5:
		printf("%16s", "baking");
		break;
	case 6:
		printf("%16s", "house wares");
		break;
	case 7:
		printf("%16s", "miscellaneous");
		break;

	}


}

void centreText(int symbolCount, char symbol, char text[])
{
	int i;
	int symbolWithTextLen = (symbolCount - strlen(text)) / 2;

	if (strlen(text) == 0)
	{
		for (i = 0; i < symbolCount; i++)
		{
			printf("%c", symbol);
		}
	}
	else if (strlen(text) % 2 == 0)
	{
		for (i = 0; i < symbolWithTextLen; i++)
		{
			printf("%c", symbol);
		}
		printf("%s", text);
		for (i = 0; i < symbolWithTextLen; i++)
		{
			printf("%c", symbol);
		}
	}
	else {
		for (i = 0; i < symbolWithTextLen; i++)
		{
			printf("%c", symbol);
		}
		printf("%s", text);
		for (i = 0; i <= symbolWithTextLen; i++)
		{
			printf("%c", symbol);
		}
	}
}

void printStockReport(struct StockRecord stockRecord[], int amount)
{
	int i, id = 1;


	printf("%4s%31s%16s%8s%10s", "ID", "Product", "Category", "Price", "Quantity\n");

	for (i = 0; i < amount; i++)
	{

		if (stockRecord[i].stockInfo.price != 0)
		{
			printf("%4d%31s", stockRecord[i].id, stockRecord[i].itemName);
			productType(&stockRecord[i]);
			printf("%8.2lf%9.0lf\n", stockRecord[i].stockInfo.price, stockRecord[i].quantity);

		}
	}
}




int readSale(struct StockRecord stockRecord[], int numOfStockItems, struct SalesRecord salesRecord[])
{
	int i = 0, index, j, id = 0, keepGoing = 1, salesCounter = 0, adding = 1;
	double quantity;


	for (i = 0; i < numOfStockItems; i++)
	{
		salesRecord[i].amountSold = 0;
	}

	do
	{

		printf("Enter a product ID to purchase, and the quantity (0 to stop): ");
		scanf("%d,%lf", &id, &quantity);

		for (i = 0; i < numOfStockItems && id != 0; i++)
		{
			do
			{
				if (id < stockRecord[0].id || id > numOfStockItems)
				{
					printf("Invalid Product - Enter a number between %d and %d: ", stockRecord[0].id, numOfStockItems);
					scanf("%d,%lf", &id, &quantity);
				}

				if (quantity < 0.10 || quantity > 100.00)
				{
					printf("Invalid quantity - Enter a number between 0.10 and 100.00: ");
					scanf("%d,%lf", &id, &quantity);
				}
				else
				{
					keepGoing = 0;
				}
				if (id == stockRecord[i].id)
				{
					salesCounter++;
					index = id - 1;
					salesRecord[index].stockRecord = stockRecord[i];
					salesRecord[index].stockRecord.stockInfo = stockRecord[i].stockInfo;


					for (j = 0; j < quantity && stockRecord[i].quantity > 0; j++)
					{

						stockRecord[i].quantity--;
						stockRecord[i].stockInfo.amount++;
						salesRecord[index].amountSold++;
						keepGoing = 0;

					}
				}


			} while (keepGoing);

		}
	} while (id != 0);


	return salesCounter;
}

double printSalesReport(const struct StockRecord stockRecord[], struct SalesRecord salesRecord[], int numOfSaleItems)
{
	int i = 0, keepGoing = 1;
	double total = 0, tax = 0, finalTotal = 0;

	puts("");
	puts("");
	centreText(70, '*', " Seneca Groceries ");
	puts("");
	centreText(70, '=', "");
	puts("");


	for (i = 0; i < MAX_ITEMS_IN_SALE; i++)
	{

		if (salesRecord[i].amountSold > 0)
		{
			printf("%30s%9.2lf%8.2lf", salesRecord[i].stockRecord.itemName, (salesRecord[i].stockRecord.stockInfo.price * salesRecord[i].amountSold), salesRecord[i].stockRecord.stockInfo.price);
			puts("");

			total = total + (salesRecord[i].stockRecord.stockInfo.price * salesRecord[i].amountSold);

			if (salesRecord[i].stockRecord.stockInfo.category == 6 || salesRecord[i].stockRecord.stockInfo.category == 7)
			{
				tax = tax + (salesRecord[i].stockRecord.stockInfo.price * salesRecord[i].amountSold) * 0.13;
			}
		}
	}



	printf("%s%33.2lf\n", "Purchase Total", total);
	printf("%s%44.2lf\n", "Tax", tax);
	finalTotal = total + tax;
	printf("%s%42.2lf\n", "Total", finalTotal);
	printf("Thank you for shopping at Seneca!");
	puts("");
	puts("");

	return total;
}
void swap(struct SalesRecord* switch1, struct SalesRecord* switch2)
{
	struct SalesRecord temp = *switch1;

	*switch1 = *switch2;
	*switch2 = temp;
}

void sort(struct SalesRecord salesRecord[], int iterator)
{
	int curPass, iterIdx;

	for (curPass = iterator - 1; curPass > 0; curPass--)
	{
		for (iterIdx = 0; iterIdx < curPass; iterIdx++)
		{
			if (salesRecord[iterIdx].stockRecord.stockInfo.amount < salesRecord[iterIdx + 1].stockRecord.stockInfo.amount)
			{
				swap(&salesRecord[iterIdx], &salesRecord[iterIdx + 1]);
			}
		}
	}
}

void getTopSellers(struct StockRecord stockRecord[], int numStockItems, struct SalesRecord salesRecord[], int rank, int category)
{

	int iterIdx, k, curPass, i, keepGoing = 1;

	struct SalesRecord temp[MAX_ITEMS_IN_SALE] = { {0} };

	for (k = 0; k <= numStockItems; k++)
	{
		if (stockRecord[k].stockInfo.category == category + 1)
		{
			if (stockRecord[k].stockInfo.amount > 0)
			{
				temp[k].stockRecord = stockRecord[k];
			}

		}

	}

	sort(temp, numStockItems);

	for (i = 0; i < rank; i++)
	{
		if (strlen(temp[i].stockRecord.itemName) == 0)
		{
			strcpy(salesRecord[i].stockRecord.itemName, "<none>");
			salesRecord[i].stockRecord.stockInfo.amount = 0.00;
		}
		else
		{
			salesRecord[i] = temp[i];
		}
	}
}

void printTopSellersHeader(int category)
{
	switch (category)
	{
	case 1:
		centreText(50, '-', "Top 3 sellers in produce");
		break;
	case 2:
		centreText(50, '-', "Top 3 sellers in bakery");
		break;
	case 3:
		centreText(50, '-', "Top 3 sellers in meat");
		break;
	case 4:
		centreText(50, '-', "Top 3 sellers in dairy");
		break;
	case 5:
		centreText(50, '-', "Top 3 sellers in baking");
		break;
	case 6:
		centreText(50, '-', "Top 3 sellers in house wares");
		break;
	case 7:
		centreText(50, '-', "Top 3 sellers in miscellaneous");
		break;
	}
}


void printTopSellers(struct StockRecord stockRecord[], const struct SalesRecord salesRecord[], int rank, int category)
{
	int i, k;

	printTopSellersHeader(category +1);
	puts("");

	for (i = 0; i < rank; i++)
	{
		printf("%d%34s%8.2lf\n", i + 1, salesRecord[i].stockRecord.itemName, salesRecord[i].stockRecord.stockInfo.amount);
	}
}
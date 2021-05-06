/*
Name:		 Adam Springett
ID:			 130751209
Email:		 aspringett@myseneca.ca
Section:	 NOO
Date:		 Dec 6, 2020
*/

#ifndef STOCK_H_
#define STOCK_H_

#define MAX_ITEMS_IN_SALE 100
#define NUM_CATS 7

struct StockInfo
{
	double amount;
	int category;
	double price;
	int byWeight;
};

struct StockRecord
{
	struct StockInfo stockInfo;
	int id;
	double quantity;
	char itemName[31];
};

struct SalesRecord
{
	struct StockRecord stockRecord;
	double amountSold;
};

//clears buffer after [^/n] character at the end of a string in a scanf function
void clearBuffer(void);

//read user input stock items and store them in array of stockRecord struct
int readStockItems(struct StockRecord stockRecord[], int max, int input);

//used in print stock to display a string to replace the integer stored for category
void productType(struct StockRecord stockRecord[]);

//takes symbols, symbol count and text and centres and prints all together
void centreText(int symbolCount, char symbol, char text[]);

//prints stored stock information
void printStockReport(struct StockRecord stockrecord[], int amount);

//read the sales made, subtract sales from stock, and save sales in salesRecord
int readSale(struct StockRecord stockRecord[], int numOfStockItems, struct SalesRecord salesRecord[]);

//print the sales purchased, calculate the amounts in sales and return the total before tax
double printSalesReport(const struct StockRecord stockRecord[], struct SalesRecord salesRecord[], int numOfSaleItems);

//swap the arrays of SalesRecord from sort in order to order them
void swap(struct SalesRecord* switch1, struct SalesRecord* switch2);

//bubble sorting to order salesRecord from most sold to least sold
void sort(struct SalesRecord salesRecord[], int iterator);

//divides up items sold by catagories and stores them in an array of salesRecord struct
void getTopSellers(struct StockRecord stockRecord[], int numStockItems, struct SalesRecord salesRecord[], int rank, int category);

//calls on the centreText function to print off the header of each category for displaying top sales
void printTopSellersHeader(int category);

//prints top 3 sales for food items and top 2 sales for house wares and miscellaneous items
void printTopSellers(struct StockRecord stockRecord[], const struct SalesRecord salesRecord[], int rank, int category);

#endif
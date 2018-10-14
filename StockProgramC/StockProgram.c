/* 
 * File:   StockProgram.c
 * Author: Daniel Banks
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Inventory.h"
#include "Sales.h"
#include "StockItem.h"

typedef int bool;
#define true 1
#define false 0

FILE *efopen(char *filename, char *mode);
InvList *loadInventory(FILE *invFile);
SalesList *applySales(FILE *salesFile, InvList *invList);
int * bestSalesDay(SalesList *salesList);
int countNPNTrans(InvList *invList);
double totalResistance(InvList *invList);

int main(int argc, char** argv) {

    //Open Inventory file
    FILE *invFile = efopen("inventory.txt", "r");
    FILE *salesFile = efopen("sales.txt", "r");

    //Load inventory into LinkedList
    InvList* invList = loadInventory(invFile);

    //Test Printing Inventory List
    //    printf("\n\n");
    //    printf("invList - \n");
    //    inv_list_fprint(invList);

    //Apply sales to the inventory list and load into the sales list
    SalesList* salesList = applySales(salesFile, invList);
    
    //Print the sales list
    printf("\n\n");
    printf("salesList - \n");
    sales_list_fprint(salesList);

    //    printf("\n\n");
    //    printf("invList ------------------------------------------------------------ \n");
    //    inv_list_fprint(invList);
    
    //Sort by price, then print the inventory List
    inv_list_sort(invList);
    printf("\n\n");
    printf("invList Sorted ---------------------------------------------- \n");
    inv_list_fprint(invList);

    //Determine best sales day then output
    int *bestDay = bestSalesDay(salesList);
    printf("\n");
    printf("Best Day: %d/%d/%d", bestDay[0], bestDay[1], bestDay[2]);
    printf("\n");
    double amount = (double)bestDay[3]/100;
    printf("Amount Made: %f", amount);
    printf("\n");
    printf("Number of Items sold: %d", bestDay[4]);
    printf("\n");

    //Count the number of NPN transistors left in stock
    int npnStock = countNPNTrans(invList);
    printf("\n");
    printf("NPN Stock: %d", npnStock);
    
    //Calculate the total resistance of all resistors in stock
    double totalRes = totalResistance(invList);
    printf("\n");
    printf("Total Resistance: %f", totalRes);

    fclose(invFile);
    fclose(salesFile);

    return (EXIT_SUCCESS);
}

/**
 * Open File Function
 * @param filename
 * @param mode
 * @return FILE pointer
 */
FILE *efopen(char *filename, char *mode) {
    FILE *fd = fopen(filename, mode);

    if (fd == NULL) {
        printf(stderr, "Error: unable to open '%s' in mode '%s'\n", filename, mode);

        exit(EXIT_FAILURE);
    }
    return fd;
}

/**
 * Load inventory into LinkedList Function
 * @param invFile
 * @return InvList pointer
 */
InvList *loadInventory(FILE *invFile) {
    FILE* fp = invFile;
    InvList *list = inv_list_new();
    const char delim[1] = ",";
    char *token;
    char *type;
    char *stockCode;
    int stockLevel=0;
    int price=0;
    char *details;
    char line[50];
    int i=0;

    if (fp != NULL) {
        while (fgets(line, 50, fp) != NULL) {
            //            printf(line);
            token = strtok(line, delim);

            i = 0;
            while (token != NULL) {
                //               printf("%s\n", token);
                switch (i) {
                    case 0:
                        type = token;
                        break;
                    case 1:
                        stockCode = token;
                        break;
                    case 2:
                        stockLevel = atoi(token);
                        break;
                    case 3:
                        price = atoi(token);
                        details = NULL;
                        break;
                    case 4:
                        details = token;
                        break;
                    default:
                        fprintf(stderr, "Token out of bounds, too many parameters for stock item. \n");
                }
                i++;
                token = strtok(NULL, delim);
            }
            stockItem item = {type, stockCode, stockLevel, price, details};
            inv_list_add(list, &item);
            //            printItem(&item);
        }
    }
    return list;
}

/**
 * Function to read sales.txt, apply sales to the inventory list and store 
 * successful sales in a salesList
 * @param salesFile
 * @param invList
 * @return SalesList pointer
 */
SalesList *applySales(FILE *salesFile, InvList *invList) {
    FILE* fp = salesFile;
    InvList* invp = invList;
    SalesList *salesList = sales_list_new();

    const char delim[2] = "/,";
    char *token;
    bool success;
    bool found;
    int day=0;
    int month=0;
    int year=0;
    char* stockCode;
    int quantity=0;
    stockItem* item;
    char line[50];
    int i=0;

    if (fp != NULL) {
        //Read in line from files
        while (fgets(line, 50, fp) != NULL) {
            success = false;
            found = false;
            //break the line into tokens using , & / delimiters
            token = strtok(line, delim);

            i = 0;
            while (token != NULL) {
                switch (i) {
                    case 0:
                        day = atoi(token);
                        break;
                    case 1:
                        month = atoi(token);
                        break;
                    case 2:
                        year = atoi(token);
                        break;
                    case 3:
                        stockCode = token;
                        break;
                    case 4:
                        quantity = atoi(token);
                        break;
                    default:
                        printf("Token out of bounds, too many parameters for sales item. \n");
                }
                i++;
                token = strtok(NULL, delim);
            }
            InvNode *node = invp->first;
            for (node; node != NULL; node = node->next) {
                
                if (strcmp(node->item->stockCode, stockCode) == 0) {
                    found = true;
                    //printf("ItemCode: %s \n", node->item->stockCode);
                    //printf("saleCode: %s \n\n", stockCode);

                    if (node->item->stockLevel >= quantity) {
                        success = true;
                        setStockLevel(node->item, node->item->stockLevel - quantity);
                        item = node->item;
                    } else {
                        success = false;
                        fprintf(stderr, "Item %s stock level %d is too low to apply sale of %d items.\n", node->item->stockCode, node->item->stockLevel, quantity);
                    }
                    break;
                }
            }

            if (!found)
                printf("Item %s not found in inventory.\n", stockCode);

            if (success) {
                int date = 10000 * year + 100 * month + day;
                SalesItem salesItem = {item, date, day, month, year, quantity};
                sales_list_add(salesList, &salesItem);
                //                printf("Added: ");
                //                printSalesItem(&salesItem);
            }
        }
    }
    return salesList;
}

/**
 * Determine the date with the highest sales volume (Most money made in one day)
 * @param salesList
 * @return Int Array
 */
int * bestSalesDay(SalesList *salesList) {
    static int maxDateArray[5];
    int count=0;
    int numSold=0;
    int maxNumSold=0;
    int currentDate=0;
    int lastDate=0;
    int max=0;
    int maxDate=0;

    SalesNode *node = salesList->first;
    lastDate = node->salesItem->date;

    for (node; node != NULL; node = node->next) {
        currentDate = node->salesItem->date;

        if (currentDate == lastDate) {
            count += node->salesItem->numSold * node->salesItem->item->price;
            numSold += node->salesItem->numSold;
        } else if (count > max) {
            max = count;
            maxDate = lastDate;
            maxNumSold = numSold;
            count = node->salesItem->numSold * node->salesItem->item->price;
            numSold = node->salesItem->numSold;
        } else {
            count = node->salesItem->numSold * node->salesItem->item->price;
            numSold = node->salesItem->numSold;
            
        }

        lastDate = currentDate;
    }

    SalesNode *secondNode = salesList->first;
    for (secondNode; secondNode != NULL; secondNode = secondNode->next) {
        if (secondNode->salesItem->date == maxDate) {
            maxDateArray[0] = secondNode->salesItem->day;
            maxDateArray[1] = secondNode->salesItem->month;
            maxDateArray[2] = secondNode->salesItem->year;
            maxDateArray[3] = max;
            maxDateArray[4] = maxNumSold;
            break;
        }
    }
    
    return maxDateArray;
}

/**
 * Determine many NPN transistors are in stock after processing all sales
 * @param invList
 * @return int
 */
int countNPNTrans(InvList *invList) {
    int count = 0;

    InvNode *node = invList->first;
    for (node; node != NULL; node = node->next) {
        if (node->item->details != NULL) {
            if (strstr(node->item->details, "NPN") != NULL) {
                count += node->item->stockLevel;
            }
        }
    }

    return count;
}

/**
 * Calculate resistance of all resistors in stock
 * @param invList
 * @return double
 */
double totalResistance(InvList *invList) {
    double count = 0;

    InvNode *node = invList->first;
    for (node; node != NULL; node = node->next) {
        if (strstr(node->item->type, "resistor") != NULL && node->item->stockLevel > 0) {
            //Full details
            char *str = node->item->details;
            
            //buffer for strtol
            char *ptr;
            
            //First digit
            double num1;
            num1 = strtol(str, &ptr, 10);
            
            //Get remaining number
            char *num2Char = ptr + 1;
            double num2 = atoi(num2Char);
            
            double countEach=0.0;
            
            if (strstr(ptr, "R") != NULL) {
                if (num2 > 0) {
                    countEach = (num1 + (num2 / 10)) * node->item->stockLevel;
                    count += (num1 + (num2 / 10)) * node->item->stockLevel;
                } else {
                    countEach = num1 * node->item->stockLevel;
                    count += num1 * node->item->stockLevel;
                }
            } else if (strstr(ptr, "K") != NULL) {
                if (num2 > 0) {
                    countEach = ((num1 + (num2 / 10))*1000) * node->item->stockLevel;
                    count += ((num1 + (num2 / 10))*1000) * node->item->stockLevel;
                } else {
                    countEach = (num1 * 1000) * node->item->stockLevel;
                    count += (num1 * 1000) * node->item->stockLevel;
                }
            } else if (strstr(ptr, "M") != NULL) {
                if (num2 > 0) {
                    countEach = ((num1 + (num2 / 10))*1000000) * node->item->stockLevel;
                    count += ((num1 + (num2 / 10))*1000000) * node->item->stockLevel;
                } else {
                    countEach = (num1 * 1000000) * node->item->stockLevel;
                    count += (num1 * 1000000) * node->item->stockLevel;
                }
            }
            
            // Test Code
//            printf("\n");
//            printf("Item: %s \n", node->item->stockCode);
//            printf("Stock Level: %d\n", node->item->stockLevel);
//            printf("Resistance: %s", str);
//            printf("ptr: %s", ptr);
//            printf("num1: %f\n", num1);
//            printf("num2Char: %s", num2Char);
//            printf("num2: %f\n", num2/10);
//            printf("CountEach: %f \n", countEach);
//            printf("Count: %f", count);
//            printf("\n");

        }
    }

    return count;
}
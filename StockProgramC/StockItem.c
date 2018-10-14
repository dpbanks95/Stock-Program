/* 
 * File:   StockItem.c
 * Author: Daniel Banks
 */

#include <stdio.h>
#include <stdlib.h>
#include "StockItem.h"

char* getType(stockItem* item)
{
    return item->type;
}

char* getStockCode(stockItem* item)
{
    return item->stockCode;
}

int getStockLevel(stockItem* item)
{
    return item->stockLevel;
}

int getPrice(stockItem* item)
{
    return item->price;
}

void setType(stockItem* item, char* newType)
{
    item->type = newType;
}

void setStockCode(stockItem* item, char* newStockCode)
{
    item->stockCode = newStockCode;
}

void setStockLevel(stockItem* item, int newStockLevel)
{
    item->stockLevel = newStockLevel;
}

void setPrice(stockItem* item, int newPrice)
{
    item->price = newPrice;
}

char* getDetails(stockItem* item)
{
    return item->details;
}

void setDetails(stockItem* item, char* newDetails)
{
    item->details = newDetails;
}

void printItem(stockItem* item)
{
    printf("%10s, ", item->type);
    printf("%13s, ", item->stockCode);
    printf("%4d, ", item->stockLevel);
    if(item->details!=NULL){
        printf("%3d, ", item->price);
        printf("%17s", item->details);        
    }
    else{
        printf("%3d", item->price);
        printf("\n");        
    }
}
/* 
 * File:   StockItem.h
 * Author: Daniel Banks
 */

#ifndef STOCKITEM_H
#define	STOCKITEM_H

typedef struct stockItemStruct
{
    char *type;
    char *stockCode;
    int stockLevel;
    int price;
    char *details;
    
} stockItem;

char* getType(stockItem* item);
char* getStockCode(stockItem* item);
int getStockLevel(stockItem* item);
int getPrice(stockItem* item);
char* getDetails(stockItem* item);

void setType(stockItem* item, char* newType);
void setStockCode(stockItem* item, char* newStockCode);
void setStockLevel(stockItem* item, int newStockLevel);
void setPrice(stockItem* item, int newPrice);
void setDetails(stockItem* item, char* newDetails);
void printItem(stockItem* item);

#endif	/* STOCKITEM_H */